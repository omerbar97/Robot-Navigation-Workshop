import './Live.css';
import get from '../../services/getServices';
import post from '../../services/postServices';
import LiveGridMap from '../Map/LiveGridMap';
import RobotLiveData from '../Info/RobotLiveData';
import { useEffect, useState } from 'react';

async function getImgFromServerAndStartRobot(setImg) {
    let res = await get.Map();
    console.log(res);
    if (res === null) {
        // failed to retrive the map
        alert("failed to retrive the map, try again later");
        return;
    }
    setImg(res);
    post.startRobotSimulator();
    post.startRobot();
}


function Live(props) {

    const { uploadMap, uploadConfigRooms, uploadRobotConfigurations, serverOnline } = props;

    const [isLive, setIsLive] = useState(false);
    const [img, setImg] = useState(null); // the map image
    const handleStartBtn = (event) => {
        event.preventDefault();
        if (!uploadMap || !uploadConfigRooms || !uploadRobotConfigurations) {
            alert("You should first upload the neccesry files!");
            return;
        }
        if (serverOnline === false) {
            alert("You should first connect to the robot-server!");
            return;
        }
        setIsLive(true);
    }

    const handleStopBtn = async (event) => {
        event.preventDefault();
        // calling the server to stop the robot
        post.stopRobotSimulator();
        setIsLive(false);
    }

    useEffect(() => {
        if (isLive) {
            // getting the map from the server
            getImgFromServerAndStartRobot(setImg);
        }
    }, [isLive])

    return (
        <div className={`conatiner live-page mt-5 ${isLive ? 'extend-height' : ''}`}>
            <h4>
                <u><b>This is the live broadcast page, from here you can see the robot's movements in real time.</b></u>
            </h4>
            <div className="row"> {
                !isLive && (
                    <div className='col-6 right'>
                        <button
                            className='btn btn-warning'
                            onClick={handleStartBtn}>START ROBOT</button>
                    </div>
                )
            }
                {
                    isLive && img && (
                        <div className='col-6 right'>
                            <button
                                className='btn btn-danger'
                                onClick={handleStopBtn}>STOP ROBOT</button>
                        </div>
                    )
                }
            </div>
            {isLive && img && (<div className='d-flex container-live'>
                <div className='col-7'>
                    {/* here the map going to be */}
                    <LiveGridMap img={img} />
                </div>
                <div className='col-5'>
                    <RobotLiveData />
                </div>
            </div>

            )}
        </div>
    );
}

export default Live;