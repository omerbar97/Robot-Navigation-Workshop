import { useState, useEffect } from 'react';
import './RobotLiveData.css'
import WebSocketClient from '../../services/WebSocketClient';



function RobotLiveData(props) {

    const [robotOnline, setRobotOnline] = useState(false);
    const [stageOnline, setStageOnline] = useState(false);

    const ws = new WebSocketClient("ws://localhost:8081");
    
    ws.ws.addEventListener('message', (event) => {
        let dataJson = JSON.parse(event.data);
        console.log(dataJson);
        if (dataJson.type === "stageInit" && dataJson.success) {
            console.log("stage is online");
            setStageOnline(true);
        }
    });


    return (
        <div className=''>
            <h2><b><u>Robot Live Data</u></b></h2>
            <div className='row'>
                <div className='col-1'>
                    {
                        !stageOnline && (
                            <span className={`spinner-border text-danger ${robotOnline ? 'connected' : ''}`} role="status">
                                <span className="sr-only">Loading...</span>
                            </span>
                        )
                    }

                </div>
                <div className='col-6 mt-1'>
                    <h5 className={`connection-status ${stageOnline ? 'connected' : ''}`}
                    >Stage Connection</h5>
                </div>
            </div>
            <div className='row'>
                <div className='col-1'>
                {
                        !robotOnline && (
                            <span className={`spinner-border text-danger ${robotOnline ? 'connected' : ''}`} role="status">
                                <span className="sr-only">Loading...</span>
                            </span>
                        )
                    }

                </div>
                <div className='col-6 mt-1'>
                    <h5 className={`connection-status ${robotOnline ? 'connected' : ''}`}
                    >Robot Connection</h5>
                </div>
            </div>

        </div>
    )
}

export default RobotLiveData;