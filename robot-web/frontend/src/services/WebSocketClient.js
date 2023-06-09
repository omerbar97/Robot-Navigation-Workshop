
class WebSocketClient {
  constructor(serverUrl) {
    this.ws = new WebSocket(serverUrl);

    // WebSocket connection opened
    this.ws.addEventListener('open', () => {
      console.log('Connected to WebSocket server');
    });

    // WebSocket message received

    // WebSocket connection closed
    this.ws.addEventListener('close', () => {
      console.log('Disconnected from WebSocket server');
    });
  }

  send(message) {
    this.ws.send(message);
  }
}

module.exports = WebSocketClient;
