
const WebSocketClient = require('../services/WebSocketClient.js');
let wsClient;
const startWsServer = (req, res) => {
    // starting the websocket server
    // getting the ip and port from the req
    let data = req.body;
    if(!data) {
        res.status(400).send('Bad Request');
        return;
    } else if(!data.url) {
        res.status(400).send('Bad Request');
        return;
    }
    // creating the websocket client
    wsClient = new WebSocketClient(data.url);

};

module.exports = wsClient;

module.exports = {
    startWsServer
};