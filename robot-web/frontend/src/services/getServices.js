import SERVER from './api'

// all the server get request

const Map = async () => {
    // getting the map from the server
    try {
        const response = await fetch(SERVER + 'map', {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json'
            },
        });
        if(response.ok){
            console.log("map received from server");
            return await response.text();
        }
        else{
            console.log("failed to receive map from the server");
        }
        return null;
    } catch (error) {
        console.log(error);
    }
    return null;
}

const get = {
    Map,
}

export default get;
