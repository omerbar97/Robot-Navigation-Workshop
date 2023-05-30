const mapServices = require('../services/map.js');
const { addMapToDB,
    addRoomsToDB,
    getMapFromDB,
    getRoomsFromDB } = require('../models/mapModel.js');


const postMap = async (req, res) => {
    // getting the map from the request body
    let data = req.body;
    if(!data) {
        res.status(400).send('Bad Request');
        return;
    }else if(!data.map) {
        res.status(400).send('Bad Request');
        return;
    }
    await addMapToDB(data.map);
    data = await getMapFromDB();
    console.log(data);
    res.status(200).send('OK');
    
};

const postRooms = async (req, res) => {
    // getting the map from the request body
    let data = req.body;
    console.log(data);
    if(!data) {
        res.status(400).send('Bad Request');
        return;
    }else if(!data.text) {
        res.status(400).send('Bad Request');
        return;
    }
    await addRoomsToDB(data.text)
    data = await getRoomsFromDB();
    console.log(data);
    res.status(200).send('OK');
    
};

module.exports = {
    postMap,
    postRooms
};
