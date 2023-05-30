const { addIp,
    addPort,
    addCfg,
    addWorld } = require('../models/robotModel');

// saving the robot information from the client
const postRobotSimulation = (req, res) => {
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
    addIp(data.ip);
    addPort(data.port);
    addCfg(data.cfg);
    addWorld(data.world);
    
};