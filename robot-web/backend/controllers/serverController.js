const WebSocketClient = require('../services/WebSocketClient.js');
let wsClient;

const connectToServer = (req, res) => {
    let data = req.body;
    console.log(data);
    if (!data) {
        res.status(400).send('wrong input');
        return;
    } else if (!data.ip) {
        res.status(400).send('wrong input');
        return;
    }
    try {
        wsClient = new WebSocketClient(data.ip);
        wsClient.connect();
        // waiting 4 seconds for the robot to start
        setTimeout(() => {
            if (wsClient.online === true) {
                // connected to the server
                res.status(200).send('OK');
            } else {
                // not connected to the server
                res.status(401).send('Failed to connect to the server, maybe server is not online?');
            }
        }, 1000);
    } catch(error) {
        console.log(error);
    }

};

module.exports = {
    connectToServer,
    wsClient,
};
