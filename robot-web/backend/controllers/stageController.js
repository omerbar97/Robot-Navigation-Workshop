const {  getCfg,
    getWorld } = require("../models/robotModel.js");
const { getMapFromDB } = require("../models/mapModel.js");

const getConfig = async (req, res) => {
    // returning the config of the stage program
    // {
    //     "world": ".world file",
    //     "cfg" : ".cfg file",
    //     "map": "png map",
    // }

    // getting the data from the database
    let cfg = await getCfg();
    let world = await getWorld();
    let map = await getMapFromDB();


    let dataToSend = {
        "world": world,
        "cfg": cfg,
        "map": map
    }

    // sending the response
    res.status(200).send(JSON.stringify(dataToSend));
}

module.exports = {
    getConfig,
}