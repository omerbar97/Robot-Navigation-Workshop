const WebSocket = require('ws');

class WebSocketServer {
    constructor(port) {
        this.port = port;
        this.clients = new Set();
        this.server = null;
    }

    start() {
        this.server = new WebSocket.Server({ port: this.port });

        this.server.on('connection', (ws) => {
            console.log('A new client connected');
            this.clients.add(ws);

            ws.on('message', (message) => {
                console.log(`Received message: ${message}`);

                // Process the received message here or perform any necessary actions

                // Send a response back to the client
                ws.send('Received your message');
            });

            ws.on('close', () => {
                console.log('Client disconnected');
                this.clients.delete(ws);
            });
        });

        console.log(`WebSocket server started on port ${this.port}`);
    }

    broadcast(message) {
        this.clients.forEach((client) => {
            if (client.readyState === WebSocket.OPEN) {
                client.send(JSON.stringify(message));
            }
        });
    }
}

const instance = new WebSocketServer(8081);
instance.start();

module.exports = instance;
