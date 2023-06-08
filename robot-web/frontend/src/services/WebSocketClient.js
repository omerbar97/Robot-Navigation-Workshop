// const WebSocket = require('ws');

let instance = null;

class WebSocketClient {
  constructor(serverUrl) {
    if (!instance) {
      console.log('Creating new instance of WebSocketClient');
      this.serverUrl = serverUrl;
      this.online = false;
      this.ws = null;
      instance = this;
      this.connect();
    }
    console.log('Returning instance of WebSocketClient');
    return instance;
  }

  connect() {
    try {
      this.ws = new WebSocket(this.serverUrl);

      // WebSocket connection opened
      this.ws.addEventListener('open', () => {
        console.log('Connected to WebSocket server');
        this.send('Hello from browser-client!');
        this.online = true;
      });

      // WebSocket connection closed
      this.ws.addEventListener('close', () => {
        console.log('Disconnected from WebSocket server');
        instance = null;
        this.online = false;
      });

      this.ws.addEventListener('error', (error) => {
        console.log('WebSocket connection error:', error.message);
      });
      

    } catch (error) {
      console.log('Failed to connect to WebSocket server:', error.message);
      this.online = false;
      instance = null;
    }
  }

  send(message) {
    if (this.ws && this.ws.readyState === WebSocket.OPEN) {
      this.ws.send(message);
    } else {
      console.log('WebSocket connection is not open. (from browser-client)');
    }
  }

  changeServerUrl(newServerUrl) {
    if (this.ws) {
      this.ws.close();
      this.online = false;
      instance = null;
    }

    this.serverUrl = newServerUrl;
    this.connect();
  }
}

module.exports = WebSocketClient;
