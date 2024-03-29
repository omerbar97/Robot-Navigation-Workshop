
import React from 'react';
import NavBar from '../Navbars/NavBar';
import GridMap from '../Map/GridMap';
import ConfigForm from '../Forms/ConfigForm';
import UploadForm from '../Forms/UploadForm';
import './Config.css';
import { useState, useRef } from 'react'
import ServerForm from '../Forms/ServerForm';

const ConfigPage = (props) => {

  const { setUploadMap, setUploadConfigRooms, serverInfo, setServerIp, setServerOnline, serverIp } = props;

  const [newConfig, setNewConfig] = useState(false);
  const [img, setImg] = useState(null);
  const [scale, setScale] = useState(5); // each pixel is represented by 5px
  const [centerRoom, setCenterRoom] = useState("undefined");
  const [enterRoom, setEnterRoom] = useState("undefined");
  const [exitRoom, setExitRoom] = useState("undefined");
  const [id, setId] = useState(null);
  const [roomID, setRoomID] = useState(1);
  let inputRef = useRef(null);

  const handleClick = (event) => {
    event.preventDefault();
    setNewConfig(true);
  }

  if (!newConfig) {
    // rendering only the button to add the config and map files
    return (
      <>
        {
          serverInfo === true && (
            <div className='server-side mt-2'>
              <ServerForm setServerIp={setServerIp} setServerOnline={setServerOnline} serverIp={serverIp} />
            </div>
          )
        }
        <div className='container'>
          <div className='row mt-2'>
            <div className='item-config'>
              <button className='btn btn-info shadow'
                onClick={handleClick}
              >to create a new map configuration file click here</button>
            </div>
            <div className='robot-page'>
            <div className='col-12'>
              <UploadForm setUploadMap={setUploadMap} setUploadConfigRooms={setUploadConfigRooms} />
            </div>
          </div>
          </div>
        </div>
      </>

    )
  } else {
    return (
      <div>
        <div className='d-flex'>
          <div className='row'>
            <div className='col-6 mt-5'>
              <ConfigForm
                setImg={setImg}
                centerRoom={centerRoom}
                enterRoom={enterRoom}
                exitRoom={exitRoom}
                setId={setId}
                img={img}
                setScale={setScale}
                setUploadMap={setUploadMap}
                setUploadConfigRooms={setUploadConfigRooms}
                roomID={roomID}
                setRoomID={setRoomID} />
            </div>
            <div className='col-6'>
              <GridMap img={img}
                setCenterRoom={setCenterRoom}
                setEnterRoom={setEnterRoom}
                setExitRoom={setExitRoom}
                id={id}
                scale={scale} />
            </div>
          </div>
          <div className="row">
          </div>
        </div>
      </div>
    );
  }

};

export default ConfigPage;