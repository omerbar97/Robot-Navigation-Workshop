const { addIp,
    addPort,
    addCfg,
    addWorld } = require('../models/robotModel');

const wsClient = require('../services/WebSocketClient.js');

// saving the robot information from the client
const postRobotSimulation = async (req, res) => {
    // sending the following data
    // {
    //     "world": ".world file",
    //     "cfg" : ".cfg file",
    //     "ip": "ip address",
    //     "port": "port number"
    // }
    // checking if data is okay
    let data = req.body;
    if(!data) {
        res.status(400).send('Bad Request');
        return;
    }
    else if(!data.world) {
        res.status(400).send('Bad Request');
        return;
    }
    else if(!data.cfg) {
        res.status(400).send('Bad Request');
        return;
    }
    else if(!data.ip) {
        res.status(400).send('Bad Request');
        return;
    }
    else if(!data.port) {
        res.status(400).send('Bad Request');
        return;
    }

    // saving data to the database
    await addIp(data.ip);
    await addPort(data.port);
    await addCfg(data.cfg);
    await addWorld(data.world);

    // sending the response
    res.status(200).send('OK');
    
};

const startRobot = (req, res) => {
    // starting the robot
    // sending the following data
    wsClient.send('START_STAGE');
};

module.exports = {
    postRobotSimulation,
    startRobot
}