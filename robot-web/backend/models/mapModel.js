const { JsonDB, Config } = require('node-json-db');

const db = new JsonDB(new Config("MapAndRoom", true, false, '/'));

const addMapToDB = async (map) => {
    db.push("/map", map);
};

const addRoomsToDB = async (rooms) => {
    db.push("/rooms", rooms);
};

const getMapFromDB = async () => {
    try {
        let data = await db.getData("/map");
        return data;
    }
    catch (error) {
        console.log(error);
    }
    return null;
};

const getRoomsFromDB = async () => {
    try {
        let data = await db.getData("/rooms");
        return data;
    }
    catch (error) {
        console.log(error);
    }
    return null;
};

module.exports = {
    addMapToDB,
    addRoomsToDB,
    getMapFromDB,
    getRoomsFromDB
};

