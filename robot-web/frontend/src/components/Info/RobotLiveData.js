import { useState, useEffect } from 'react';
import './RobotLiveData.css'
import WebSocketClient from '../../services/WebSocketClient';



function RobotLiveData(props) {

    const [robotOnline, setRobotOnline] = useState(false);
    const [stageOnline, setStageOnline] = useState(false);

    const ws = new WebSocketClient("ws://localhost:8081");

    ws.ws.addEventListener('message', (event) => {
        let dataJson = JSON.parse(event.data);
        if (dataJson.type === "stageInit" && dataJson.success) {
            setStageOnline(true);
        }
        if (dataJson.type === "robotInit" && dataJson.success) {
            setRobotOnline(true);
        }
    });


    return (
        <div className=''>
            <h2><b><u>Robot Live Data</u></b></h2>
            <div className='row'>
                <div className='col-1'>
                    {
                        !stageOnline && (
                            <span className={`spinner-border text-danger ${stageOnline ? 'connected' : ''}`} role="status">
                                <span className="sr-only">Loading...</span>
                            </span>
                        )
                    }
                    {
                        stageOnline && (
                            <i class="fa-solid fa-check fa-beat-fade mt-1"></i>
                        )
                    }

                </div>
                <div className={`col-8 mt-1 ${stageOnline ? 'p-0' : ''}`}>
                    {
                        !stageOnline && (
                            <h5 className='connection-status'>Connecting to stage</h5>
                        )
                    }
                    {
                        stageOnline && (
                            <h5 className='connection-status connected'>connected to stage</h5>
                        )
                    }
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
                    {
                        robotOnline && (
                            <i class="fa-solid fa-check fa-beat-fade mt-1"></i>
                        )
                    }

                </div>
                <div className={`col-8 mt-1 ${robotOnline ? 'p-0' : ''}`}>
                    {
                        !robotOnline && (
                            <h5 className='connection-status'>Connecting to robot</h5>
                        )
                    }
                    {
                        robotOnline && (
                            <h5 className='connection-status connected'>connected to robot</h5>
                        )
                    }
                </div>
            </div>
            <div className='row'>
                {
                    robotOnline && stageOnline && (
                        <div className='col-12'>
                            {/* form to send rooms coordinate to the server */}
                            <p className='info'>Based on the room cfg that you upload, please enter 3 rooms id to travel</p>
                            <div className='row'>
                                <div className='col-3'>
                                    <input type="text" className='form-control inputInfo' placeholder='1 3 4' />
                                </div>
                                <div className='col-2'>
                                    <button className='btn btn-danger'>SEND</button>
                                </div>
                            </div>

                        </div>
                    )
                }
            </div>

        </div>
    )
}

export default RobotLiveData;