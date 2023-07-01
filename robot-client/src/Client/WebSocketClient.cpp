//
// Created by omer on 6/9/23.
//

#include "WebSocketClient.h"



WebSocketClient::WebSocketClient(RobotPlanner *planner, std::string ws) {
    // init the robot websocket connection
    this->threads = std::vector<std::thread*>();
    this->robot = planner->getRobotWrapper();
    this->planner = planner;
    this->ws = std::move(ws);
    this->wsClient.init_asio();
    this->wsClient.set_access_channels(websocketpp::log::alevel::all);
    this->wsClient.set_error_channels(websocketpp::log::elevel::all);
    this->wsClient.set_open_handler(bind(&WebSocketClient::on_open, this, ::_1));
    this->wsClient.set_close_handler(bind(&WebSocketClient::on_close, this, ::_1));
    this->wsClient.set_message_handler(bind(&WebSocketClient::on_message, this, ::_1, ::_2));
    websocketpp::lib::error_code ec;
    auto con = this->wsClient.get_connection(this->ws, ec);
    if (ec) {
        std::cout << "could not create connection because: " << ec.message() << std::endl;
        return;
    }
    this->wsClient.connect(con);
}

void WebSocketClient::on_message(websocketpp::connection_hdl hdl, client::message_ptr msg) {
    std::cout << msg->get_payload() << std::endl;
    // convert the json to a map
    auto json = nlohmann::json::parse(msg->get_payload());
    std::string type = json["type"];
    if(type == "robotTravel") {
        // sending new travel to the robot
        std::string rooms = json["rooms"];
        std::regex pattern("^[0-9 ]+$");

        if (std::regex_match(rooms, pattern)) {
            // calling the planner
            this->planner->setPlanFromString(rooms);

            if(!this->planner->isRobotInPlan()) {
                // starting new thread for executing the robot movement
                std::thread* t = new std::thread(&RobotPlanner::executePlan, this->planner);
                this->threads.push_back(t);
            } else {
//                // the robot is busy with another travel, it will be executed after the current travel
//                // creating a new thread that will wait for the current travel to finish and then execute the new travel
//                std::thread* t = new std::thread(&RobotPlanner::executePlan, this->planner);
            }
        } else {
            // the string is not in the right format
            // TODO: sending to the client errors
        }
    }
}



WebSocketClient::~WebSocketClient() {

}

void WebSocketClient::run() {
    // run the websocket client
    this->wsClient.run();
}


void WebSocketClient::sendRobotPosition() {
    // sending the robot position to the server as a json
    sleep(3);
    while(this->isOnline()){
        nlohmann::json jsonData;
        auto pos = this->robot->getCurrentPosition();
        jsonData["type"] = "robotPosition";
        jsonData["x"] = pos.first;
        jsonData["y"] = pos.second;

        this->wsClient.send(this->connection, jsonData.dump(), websocketpp::frame::opcode::text);
        sleep(3);
    }
}

void WebSocketClient::close() {
    // close the connection
    this->wsClient.close(this->connection, websocketpp::close::status::going_away, "bye from client (robot)");
    this->connection.reset();
}

bool WebSocketClient::isOnline() {
    return this->robot->isOnline();
}

void WebSocketClient::on_open(websocketpp::connection_hdl hdl) {
    // on open connection sending 'hello from client'
    this->wsClient.send(hdl, "hello from client (robot)", websocketpp::frame::opcode::text);
    this->connection = hdl;
}

void WebSocketClient::on_close(websocketpp::connection_hdl hdl) {
    // on close connection sending 'bye from client'
    this->wsClient.send(hdl, "bye from client (robot)", websocketpp::frame::opcode::text);
    this->connection.reset();

}



