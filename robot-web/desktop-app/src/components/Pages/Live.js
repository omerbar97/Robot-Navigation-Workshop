import './Live.css';
import get from '../../services/getServices';
import post from '../../services/postServices';
import LiveGridMap from '../Map/LiveGridMap';
import RobotLiveData from '../Info/RobotLiveData';
import { useEffect, useState } from 'react';

async function getImgFromServerAndStartRobot(setImg) {
    let img = await get.Map();
    if (img === null) {
        // failed to retrive the map
        alert("failed to retrive the map, try again later");
        return false;
    }
    setImg(img);
    post.startRobotSimulator();
    post.startRobot();
    return true;
}


function Live(props) {

    const { uploadMap, uploadConfigRooms, uploadRobotConfigurations, serverOnline } = props;

    const [isLive, setIsLive] = useState(false);
    const [robotCurrentPosition, setRobotCurrentPosition] = useState(null); // [x,y]
    const [isListener, setIsListener] = useState(false);
    const [img, setImg] = useState(null); // the map image
    const handleStartBtn = async (event) => {
        event.preventDefault();
        if (!uploadMap || !uploadConfigRooms || !uploadRobotConfigurations) {
            alert("You should first upload the neccesry files!");
            return;
        }
        if (serverOnline === false) {
            alert("You should first connect to the robot-server!");
            return;
        }
        let flag = await getImgFromServerAndStartRobot(setImg);
        if(flag === false) {
            alert("failed to start the stage and the robot, try again later");
            return;
        }
        setIsLive(true);
    }

    const handleStopBtn = async (event) => {
        event.preventDefault();
        // calling the server to stop the robot
        post.stopRobotSimulator();
        setImg(null);
        setIsLive(false);
        setIsListener(false);
        setRobotCurrentPosition(null);
    }

    // useEffect(() => {
    //     if (isLive) {
    //         // getting the map from the server
    //         getImgFromServerAndStartRobot(setImg);
    //     }
    // }, [isLive])

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
                    <LiveGridMap img={img} robotCurrentPosition={robotCurrentPosition}/>
                </div>
                <div className='col-5'>
                    <RobotLiveData setRobotCurrentPosition={setRobotCurrentPosition} isListener={isListener} setIsListener={setIsListener}/>
                </div>
            </div>

            )}
        </div>
    );
}

export default Live;