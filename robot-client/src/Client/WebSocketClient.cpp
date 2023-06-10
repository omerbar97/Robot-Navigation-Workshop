//
// Created by omer on 6/9/23.
//

#include "WebSocketClient.h"

WebSocketClient::WebSocketClient(RobotWrapper *robot, std::string ws) {
    // init the robot websocket connection
    this->robot = robot;
    this->ws = ws;
    this->wsClient.init_asio();
    this->wsClient.set_access_channels(websocketpp::log::alevel::all);
    this->wsClient.set_error_channels(websocketpp::log::elevel::all);
    this->wsClient.set_open_handler(bind(&WebSocketClient::on_open, this, ::_1));
    this->wsClient.set_close_handler(bind(&WebSocketClient::on_close, this, ::_1));
//    this->client.set_message_handler(bind(&WebSocketClient::on_message, this, ::_1, ::_2));
//    this->client.set_fail_handler(bind(&WebSocketClient::on_fail, this, ::_1));
//    this->client.set_pong_handler(bind(&WebSocketClient::on_pong, this, ::_1, ::_2));
//    this->client.set_interrupt_handler(bind(&WebSocketClient::on_interrupt, this, ::_1));
    websocketpp::lib::error_code ec;
    auto con = this->wsClient.get_connection(this->ws, ec);
    if (ec) {
        std::cout << "could not create connection because: " << ec.message() << std::endl;
        return;
    }
    this->wsClient.connect(con);
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
        sleep(2);
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

void WebSocketClient::sendRobotPath() {
    // sending the robot path to the server as a json
//    std::unique_lock<std::mutex> lock(mutex);
//    while (this->isOnline())
//    {
//        nlohmann::json jsonData;
//        auto path = this->robot->getRobotCurrentPath();
//        jsonData["type"] = "robotPath";
//        jsonData["path"] = path;
//        jsonData["size"] = path.size();
//
//        this->wsClient.send(this->connection, jsonData.dump(), websocketpp::frame::opcode::text);
//
//        // Wait for the value to change before continuing
//        cv.wait(lock, [] { return valueChanged; });
//
//        // Reset the valueChanged flag
//        valueChanged = false;
//
//        sleep(3);
//    }
}
