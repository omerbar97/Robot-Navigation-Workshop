//
// Created by omer on 5/31/23.
//

#include "WebSocketServer.h"

WebSocketServer::WebSocketServer(std::string ip, int port) : ip(ip), port(port), helper() {
    isStageOnline = false;
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
        this->isStageOnline = startStageProcess(hdl);
    } else if (message == "START_ROBOT" && this->isStageOnline) {
        this->currentHdl = hdl;
        startRobotControllerProcess(hdl);
    } else if(message == "STOP_STAGE" && this->isStageOnline) {
        // first checking if the child process still running
        int status;
        pid_t result = waitpid(this->stagePid, &status, WNOHANG);
        if(result == 0) {
            // killing the stage process
            kill(this->stagePid, SIGKILL);
        }
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

bool WebSocketServer::startStageProcess(websocketpp::connection_hdl hdl) {
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
        this->serverWs.send(hdl, message, websocketpp::frame::opcode::text);
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
        if (!check2) {
            // sending error message to the client
            json jsonData;
            jsonData["type"] = "stageInit";
            jsonData["success"] = false;
            jsonData["message"] = "failed to create the .cfg file";
            std::string message = jsonData.dump();
            this->serverWs.send(hdl, message, websocketpp::frame::opcode::text);
            return false;
        }

        check2 = helper.writeToFile(stageUrl + "/fromServer.world", world);
        if (!check2) {
            // sending error message to the client
            json jsonData;
            jsonData["type"] = "stageInit";
            jsonData["success"] = false;
            jsonData["message"] = "failed to create the .world file";
            std::string message = jsonData.dump();
            this->serverWs.send(hdl, message, websocketpp::frame::opcode::text);
            return false;
        }

        // creating the png file
        bool flag = helper.saveAsPng(map, stageUrl + "/bitmaps/fromServer.png");
        bool flag2 = helper.saveAsPng(map, "../maps/fromServer.png");
        int check;
        // starting
        if (flag) {
            // creating a child process
            pid_t pid = fork();
            if(pid == -1) {
                // error in fork() exiting
                json jsonData;
                jsonData["type"] = "stageInit";
                jsonData["success"] = false;
                jsonData["message"] = "failed to fork()";
                std::string message = jsonData.dump();
                this->serverWs.send(hdl, message, websocketpp::frame::opcode::text);
                return false;
            }
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
                    this->serverWs.send(hdl, message, websocketpp::frame::opcode::text);
                    exit(1);
                }
                // starting the stage process
                check = execlp("player", "player", "fromServer.cfg", NULL);
                // if got here then there was an error
                json jsonData;
                jsonData["error"] = "failed to start the stage process";
                std::string message = jsonData.dump();
                this->serverWs.send(hdl, message, websocketpp::frame::opcode::text);
                exit(1);
            } else {
                // parent process
                // the process is independant from the server
                // sending backToTheClient the success message
                // sleep for 2 seconds
                sleep(2);
                // checking if the child process is still running
                int status;
                pid_t result = waitpid(pid, &status, WNOHANG);
                if (result == 0) {
                    // the child process is still running
                    // sending backToTheClient the success message
                    json jsonData;
                    jsonData["type"] = "stageInit";
                    jsonData["success"] = true;
                    std::string message = jsonData.dump();
                    this->stagePid = pid;
                    this->serverWs.send(hdl, message, websocketpp::frame::opcode::text);
                    return true;
                } else {
                    // the child process is not running
                    // sending backToTheClient the error message
                    json jsonData;
                    jsonData["type"] = "stageInit";
                    jsonData["success"] = false;
                    jsonData["message"] = "failed to start the stage process";
                    std::string message = jsonData.dump();
                    this->serverWs.send(hdl, message, websocketpp::frame::opcode::text);
                    return false;
                }
            }
        } else {
            // error in saving the png file
            // sending backToTheClient the error message
            json jsonData;
            jsonData["type"] = "stageInit";
            jsonData["success"] = false;
            jsonData["message"] = "failed to save the png file";
            std::string message = jsonData.dump();
            this->serverWs.send(hdl, message, websocketpp::frame::opcode::text);
            return false;
        }
    }
}

bool WebSocketServer::startRobotControllerProcess(websocketpp::connection_hdl hdl) {
    // retriving the robot information from the server
    std::cout << "Starting the stage process\n";
    std::string url = "http://localhost:8080/robot/config";

    std::string response = helper.getResponse(url);
    if (response.empty()) {
        // error in handling the GET method from client
        // sending backToTheClient the error message
        // creating new json object
        json jsonData;
        jsonData["type"] = "robotInit";
        jsonData["success"] = false;
        jsonData["error"] = "failed to retrieve the robot information from the server";
        std::string message = jsonData.dump();
        this->serverWs.send(hdl, message, websocketpp::frame::opcode::text);
        return false;
    } else {
        // the format is json
        // the foramt is:
//        {
//            "ip": "string",
//            "port": "string",
//            "roomConfig": string,
//            "isStage": boolean

        json jsonData = json::parse(response);

        // saving the roomConfig file in the configures folder inside the project
        std::string roomConfig = jsonData["roomConfig"];

        // opening the file
        std::ofstream file("../configures/room_coordinates.txt");
        if (!file.is_open()) {
            // error in opening the file
            // sending backToTheClient the error message
            json jsonData;
            jsonData["type"] = "robotInit";
            jsonData["success"] = false;
            jsonData["error"] = "failed to write the roomConfig file";
            std::string message = jsonData.dump();
            this->serverWs.send(hdl, message, websocketpp::frame::opcode::text);
            return false;
        }

        // writing the roomConfig to the file
        file << roomConfig;
        file.close();
        std::string ip = jsonData["ip"];
        std::string port = jsonData["port"];
        std::string ws = jsonData["ws"];
        // starting the robot controller process
        // creating a child process
        sleep(4); // waiting for stage to start
        pid_t pid = fork();
        if(pid == -1) {
            // error in fork() exiting
            json jsonData;
            jsonData["type"] = "robotInit";
            jsonData["success"] = false;
            jsonData["message"] = "failed to fork()";
            std::string message = jsonData.dump();
            this->serverWs.send(hdl, message, websocketpp::frame::opcode::text);
            return false;
        }
        if(pid == 0) {
            // child process
            // running the robot controller process with the given ip and port
            execlp("./Robot-Navigation", "./Robot-Navigation", ip.c_str(), port.c_str(), ws.c_str(), NULL);

            // if got here then there was an error
            json jsonData;
            jsonData["type"] = "robotInit";
            jsonData["success"] = false;
            jsonData["message"] = "failed to execute the robot controller process";
            std::string message = jsonData.dump();
            this->serverWs.send(hdl, message, websocketpp::frame::opcode::text);
            exit(1);

        } else {

            // waiting for the robot controller process to start
            sleep(2);
            // checking if the child process is still running
            int status;
            pid_t result = waitpid(pid, &status, WNOHANG);
            if (result == 0) {
                // the child process is still running
                // sending backToTheClient the success message
                json jsonData;
                jsonData["type"] = "robotInit";
                jsonData["success"] = true;
                std::string message = jsonData.dump();
                this->robotPid = pid;
                this->serverWs.send(hdl, message, websocketpp::frame::opcode::text);
                return true;
            } else {
                // the child process is not running
                // sending backToTheClient the error message
                json jsonData;
                jsonData["type"] = "robotInit";
                jsonData["success"] = false;
                jsonData["message"] = "failed to start the robot controller process22";
                std::string message = jsonData.dump();
                this->serverWs.send(hdl, message, websocketpp::frame::opcode::text);
                return false;
            }
        }
    }
}
