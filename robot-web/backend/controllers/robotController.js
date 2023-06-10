const { addIp,
    addPort,
    addCfg,
    addWorld,
    getIp,
    getPort } = require('../models/robotModel');

const { getRoomsFromDB } = require('../models/mapModel');

const WebSocketClient = require('../services/WebSocketClient.js');

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
    if (!data) {
        res.status(400).send('Bad Request');
        return;
    }
    else if (!data.world) {
        res.status(400).send('Bad Request');
        return;
    }
    else if (!data.cfg) {
        res.status(400).send('Bad Request');
        return;
    }
    else if (!data.ip) {
        res.status(400).send('Bad Request');
        return;
    }
    else if (!data.port) {
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

const startStage = (req, res) => {
    // starting the robot
    // sending the following data
    let ws = new WebSocketClient(); // instance of the websocket client
    console.log("sending start_stage");
    ws.send('START_STAGE');
};

const startRobot = (req, res) => {
    let ws = new WebSocketClient(); // instance of the websocket client
    console.log("sending start_robot");
    ws.send('START_ROBOT');
};

const stopRobot = (req, res) => {
    let ws = new WebSocketClient(); // instance of the websocket client
    ws.send('STOP_STAGE');
    ws.send('STOP_ROBOT');
};

const Config = async (req, res) => {
    // returning the config of the stage program
    // {
    //     "ip": "ip address",
    //     "port" : number,
    //     "roomConfig": "File",
    //     "isStage": boolean,
    // }

    // getting the data from the database
    let ip = await getIp();
    let port = await getPort();
    let roomConfig = await getRoomsFromDB();

    if(!ip || !port || !roomConfig) {
        res.status(400).send('Bad Request');
        return;
    }
    let dataToSend = {
        "ip": ip,
        "port": port,
        "roomConfig": roomConfig,
        "isStage": true,
        "ws": "ws://localhost:8081"
    }
    console.log(dataToSend);
    // sending the response
    res.status(200).send(JSON.stringify(dataToSend));

}


module.exports = {
    postRobotSimulation,
    startStage,
    stopRobot,
    startRobot,
    Config
}