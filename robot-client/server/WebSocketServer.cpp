//
// Created by omer on 5/31/23.
//

#include "WebSocketServer.h"

WebSocketServer::WebSocketServer(std::string ip, int port) : ip(ip), port(port), helper() {
    stageUrl = "/usr/local/share/stage/worlds";

    // Initialize the WebSocket server
    serverWs.init_asio();

    // Set the callback functions
    serverWs.set_message_handler([&](websocketpp::connection_hdl hdl, server::message_ptr msg) {
        onMessage(hdl, msg);
    });
    serverWs.set_open_handler([&](websocketpp::connection_hdl hdl) {
        onOpen(hdl);
    });
    serverWs.set_close_handler([&](websocketpp::connection_hdl hdl) {
        onClose(hdl);
    });
}

WebSocketServer::~WebSocketServer() {

}

void WebSocketServer::start() {
    // Listen on all available network interfaces
    serverWs.listen(port);

    // Start accepting connections
    serverWs.start_accept();

    // Start the WebSocket server thread
    serverThread = std::thread([&]() {
        serverWs.run();
    });
}

void WebSocketServer::stop() {
    // Stop the WebSocket server
    serverWs.stop();

    // Join the server thread
    if (serverThread.joinable()) {
        serverThread.join();
    }
}

void WebSocketServer::onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg) {
    // Handle incoming message from the client
    std::string message = msg->get_payload();
    std::cout << "Message received: " << message << std::endl;
    if (message == "START_STAGE") {
        this->currentHdl = hdl;
        startStageProcess();
    }
    // Process the message as needed
}

void WebSocketServer::onOpen(websocketpp::connection_hdl hdl) {
    // Handle new client connection
    std::cout << "New client connected" << std::endl;
}

void WebSocketServer::onClose(websocketpp::connection_hdl hdl) {
    // Handle client disconnection
    std::cout << "client disconnected\n";

}

bool WebSocketServer::startStageProcess() {
    // starting the stage process
    // getting the information from the server .cfg file and .world file, establishing the connection with the server
    // and starting the stage process
    std::cout << "Starting the stage process\n";
    std::string url = "http://localhost:8080/stage/config";

    std::string response = helper.getResponse(url);
    if (response.empty()) {
        // error in handling the GET method from client
        // sending backToTheClient the error message
        // creating new json object
        json jsonData;
        jsonData["type"] = "stageInit";
        jsonData["success"] = false;
        jsonData["error"] = "failed to retrieve the .cfg and .world files from the server";
        std::string message = jsonData.dump();
        this->serverWs.send(this->currentHdl, message, websocketpp::frame::opcode::text);
        return false;
    } else {
        // the format is json
//        {
//            "cfg": "file content...",
//            "world": "file content..."
//            "map": "map content..."
//        }
        // creating a new file in the location stage/worlds
        json jsonData = json::parse(response);
        std::string cfg = jsonData["cfg"];
        std::string world = jsonData["world"];
        std::string map = jsonData["map"];

        // creating the .cfg file
        bool check2 = helper.writeToFile(stageUrl + "/fromServer.cfg", cfg);
        if(!check2) {
            // sending error message to the client
            json jsonData;
            jsonData["type"] = "stageInit";
            jsonData["success"] = false;
            jsonData["message"] = "failed to create the .cfg file";
            std::string message = jsonData.dump();
            this->serverWs.send(this->currentHdl, message, websocketpp::frame::opcode::text);
            return false;
        }

        check2 = helper.writeToFile(stageUrl + "/fromServer.world", cfg);
        if(!check2) {
            // sending error message to the client
            json jsonData;
            jsonData["type"] = "stageInit";
            jsonData["success"] = false;
            jsonData["message"] = "failed to create the .world file";
            std::string message = jsonData.dump();
            this->serverWs.send(this->currentHdl, message, websocketpp::frame::opcode::text);
            return false;
        }

        // creating the png file
        bool flag = helper.saveAsPng(map, stageUrl + "/bitmaps/fromServer.png");
        int check;
        // starting
        if (flag) {
            // creating a child process
            pid_t pid = fork();
            if (pid == 0) {
                // changing the current directory to the stage/worlds
                check = chdir(stageUrl.c_str());
                if (check == -1) {
                    // error
                    json jsonData;
                    jsonData["type"] = "stageInit";
                    jsonData["success"] = false;
                    jsonData["message"] = "failed to change directory to the stage/worlds";
                    std::string message = jsonData.dump();
                    this->serverWs.send(this->currentHdl, message, websocketpp::frame::opcode::text);
                    exit(1);
                }
                // starting the stage process
                check = execlp("player", "player", "fromServer.cfg", NULL);

                // if got here then there was an error
                json jsonData;
                jsonData["error"] = "failed to start the stage process";
                std::string message = jsonData.dump();
                this->serverWs.send(this->currentHdl, message, websocketpp::frame::opcode::text);
                exit(1);
            } else {
                // parent process
                // the process is independant from the server
                // sending backToTheClient the success message
                json jsonData;
                jsonData["type"] = "stageInit";
                jsonData["success"] = true;
                std::string message = jsonData.dump();
                this->serverWs.send(this->currentHdl, message, websocketpp::frame::opcode::text);
                return true;
            }
        } else {
            // error in saving the png file
            // sending backToTheClient the error message
            json jsonData;
            jsonData["type"] = "stageInit";
            jsonData["success"] = false;
            jsonData["message"] = "failed to save the png file";
            std::string message = jsonData.dump();
            this->serverWs.send(this->currentHdl, message, websocketpp::frame::opcode::text);
            return false;
        }
    }

}
