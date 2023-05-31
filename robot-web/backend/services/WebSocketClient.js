const WebSocket = require('ws');
const WebSocketServer = require('./WebSocketServer');

class WebSocketClient {
  constructor(serverUrl) {
    this.ws = new WebSocket(serverUrl);

    // WebSocket connection opened
    this.ws.on('open', () => {
      console.log('Connected to WebSocket server');
      this.send('Hello from client!');
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

      if (dataJson.type === "stageInit") {
        // calling service for stage init
        // brodcasting the data to all the clients
        WebSocketServer.broadcast(dataJson);
      }
    });

    // WebSocket connection closed
    this.ws.on('close', () => {
      console.log('Disconnected from WebSocket server');
    });
  }

  send(message) {
    this.ws.send(message);
  }
}

let ws;
try {
  ws = new WebSocketClient("ws://localhost:9000");
} catch (error) {
  console.log(error.message);
}


module.exports = ws;
