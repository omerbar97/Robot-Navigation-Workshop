import SERVER from './api'

// all the server post request
const newMap = async (map) => {
    // sending the map to the server
    console.log(map);
    const response = await fetch(SERVER + 'map', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(map),
    });
    if(response.ok){
        console.log("map sent to server");
    }
    else{
        console.log("failed to send map to the server");
    }
    return response;
}

const newRoomConfig = async (config) => {
    // sending the map to the server
    const response = await fetch(SERVER + 'map/rooms', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(config),
    });
    if(response.ok){
        console.log("configRoom sent to server");
    }
    else{
        console.log("failed to send configRoom to the server");
    }
    return response;
}

const newRobotSimulatorConfig = async (config) => {
    // {
    //     "world": ".world file",
    //     "cfg" : ".cfg file",
    //     "ip": "ip address",
    //     "port": "port number"
    // }

    // sending the data to the server
    try {
        const response = await fetch(SERVER + 'robot/simulator', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(config),
        });
    
        if(response.ok){
            console.log("robot simulator config files was sent to server");
        } else {
            console.log("failed to send robot simulator config to the server");
        }
        return response;
    } catch (error) {
        console.log(error);
    }
    return null;

}

const post = {
    newMap,
    newRoomConfig,
    newRobotSimulatorConfig
}
export default post;