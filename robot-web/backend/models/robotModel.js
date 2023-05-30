const { JsonDB , Config } = require('node-json-db');

const db = new JsonDB(new Config("robot", true, false, '/'));

const addIp = async (map) => {
    await db.push("/ip", map);
};

const addPort = async (rooms) => {
    await db.push("/port", rooms);
};

const addCfg = async (cfg) => {
    await db.push("/cfg", cfg);
}

const addWorld = async (world) => {
    await db.push("/world", world);
}

// getters
const getIp = async () => {
    try {
        let data = await db.getData("/ip");
        return data;
    } catch (error) {
        console.log(error);
    }
    return null;
}

const getPort = async () => {
    try {
        let data = await db.getData("/port");
        return data;
    } catch (error) {
        console.log(error);
    }
    return null;
}

const getCfg = async () => {
    try {
        let data = await db.getData("/cfg");
        return data;
    } catch (error) {
        console.log(error);
    }
    return null;
}

const getWorld = async () => {
    try {
        let data = await db.getData("/world");
        return data;
    } catch (error) {
        console.log(error);
    }
    return null;
}


module.exports = {
    addIp,
    addPort,
    addCfg,
    addWorld,
    getIp,
    getPort,
    getCfg,
    getWorld
};

