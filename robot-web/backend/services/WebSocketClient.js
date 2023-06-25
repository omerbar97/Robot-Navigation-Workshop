const WebSocket = require('ws');
const WebSocketServer = require('./WebSocketServer');
const server = require('./WebSocketServer');

let instance = null;

class WebSocketClient {
  constructor(serverUrl) {
    if (!instance) {
      this.serverUrl = serverUrl;
      this.online = false;
      this.ws = null;
      instance = this;
    }

    return instance;
  }

  connect() {
    try {
      this.ws = new WebSocket(this.serverUrl);

      // WebSocket connection opened
      this.ws.on('open', () => {
        console.log('Connected to WebSocket server');
        this.send('Hello from client!');
        this.online = true;
      });

      // WebSocket message received
      this.ws.on('message', (data) => {
        // data type is:
        // {
        //   // "type": "start",
        //   // "success": true/false
        //   // "message": "message"
        // }
        let dataJson = JSON.parse(data);

        if (dataJson.type === 'stageInit') {
          // calling service for stage init
          // broadcasting the data to all the clients
          WebSocketServer.broadcast(dataJson);
        }
        if(dataJson.type === 'robotInit') {
          // calling service for robot init
          // broadcasting the data to all the clients
          WebSocketServer.broadcast(dataJson);
        }
        if(dataJson.type === 'robotPosition') {
          // broadcasting the data to all the clients
          WebSocketServer.broadcast(dataJson);
        }
        if(dataJson.type === 'robotTravel') {
          // print
          console.log(dataJson);
        }

        console.log('Received message:', data);
      });
      
      // WebSocket connection error
      this.ws.on('error', (error) => {
        console.log('WebSocket connection error:', error.message);
        this.online = false;
      });

      // WebSocket connection closed
      this.ws.on('close', () => {
        // sending message to all the clients
        server.broadcast({
          type: 'robot-server',
          success: false,
          message: 'robot server disconnected',
        });
        console.log('Disconnected from WebSocket server');
        this.instance = null;
        this.online = false;
      });
    } catch (error) {
      console.log('Failed to connect to WebSocket server:', error.message);
      this.online = false;
    }
  }

  send(message) {
    if (this.ws && this.ws.readyState === WebSocket.OPEN) {
      this.ws.send(message);
    } else {
      console.log('WebSocket connection is not open.');
    }
  }

  changeServerUrl(newServerUrl) {
    if (this.ws) {
      this.ws.close();
      this.online = false;
    }

    this.serverUrl = newServerUrl;
    this.connect();
  }
}

module.exports = WebSocketClient;
