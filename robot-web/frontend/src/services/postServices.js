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

const post = {
    newMap,
    newRoomConfig
}
export default post;