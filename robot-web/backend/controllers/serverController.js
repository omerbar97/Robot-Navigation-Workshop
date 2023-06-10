const { getIp,
    getPort,
    getCfg,
    getWorld } = require('../models/robotModel');
const { getMapFromDB,
    getRoomsFromDB } = require('../models/mapModel');
    
const WebSocketClient = require('../services/WebSocketClient.js');
let wsClient;

const connectToServer = (req, res) => {
    let data = req.body;
    console.log(data);
    if (!data) {
        res.status(400).send('Wrong Input');
        return;
    } else if (!data.ip) {
        res.status(400).send('Wrong Input');
        return;
    }
    try {
        console.log("Trying to connect to server with ip " + data.ip);
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
    } catch (error) {
        console.log(error);
    }

};

const oldFiles = (req, res) => {
    // checking if the robot has old files configuration all ready
    // if so sending true
    let data = {
        "config": false,
        "map": false,
        "room": false,
    }
    let ip = getIp();
    let port = getPort();
    let cfg = getCfg();
    let world = getWorld();
    console.log(ip);
    if (ip && port && cfg && world) {
        data.config = true;
    }

    // checking map
    let map = getMapFromDB();
    if (map) {
        data.map = true;
    }

    // checking rooms
    let rooms = getRoomsFromDB();
    if (rooms) {
        data.room = true;
    }

    res.status(200).send(data);
};

module.exports = {
    connectToServer,
    oldFiles,
    wsClient
};
