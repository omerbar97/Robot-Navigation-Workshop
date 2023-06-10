import './App.css';
import { BrowserRouter, Route, Routes } from 'react-router-dom';
import { useEffect, useState } from 'react';
import ConfigPage from './components/Pages/Config';
import HomePage from './components/Pages/Home';
import RobotConfig from './components/Pages/RobotConfig';
import Live from './components/Pages/Live';
import NavBar from './components/Navbars/NavBar';
import get from './services/getServices';
import WebSocketClient from './services/WebSocketClient';

function App() {

  const [uploadMap, setUploadMap] = useState(false);
  const [uploadConfigRooms, setUploadConfigRooms] = useState(false);
  const [uploadRobotConfigurations, setUploadRobotConfigurations] = useState(false);
  const [isCallBack, setIsCallBack] = useState(false); // [x,y]


  // checking if the robot server has old config files
  useEffect(() => {
    async function checkOldFiles() {
      let res = await get.oldFiles();
      console.log(res);
      if (res === null) {
        // failed to retrive the map
        return;
      }
      if (res.config) {
        setUploadConfigRooms(true);
      }
      if (res.map) {
        setUploadMap(true);
      }
      if (res.room) {
        setUploadRobotConfigurations(true);
      }
    }

    const ws = new WebSocketClient("ws://localhost:8081");

    // adding the event listener
    if (ws && isCallBack === false) {
      ws.ws.addEventListener('message', (event) => {
        try {
          let t = JSON.parse(event.data);
          if (t.type === "robot-server" && t.success === false) {
            setServerOnline(t.success);
            setServerIp(null);
          }
        } catch (error) {
          console.log(error);
        }
      });
      setIsCallBack(true);
    }
    checkOldFiles();
  }, []);

  const [serverInfo, setServerInfo] = useState(false);
  const [serverOnline, setServerOnline] = useState(false);
  const [serverIp, setServerIp] = useState(null);
  const [isStage, setIsStage] = useState(false);


  return (
    <BrowserRouter>
      <NavBar uploadMap={uploadMap}
        uploadConfigRooms={uploadConfigRooms}
        uploadRobotConfigurations={uploadRobotConfigurations}
        setServerInfo={setServerInfo}
        serverInfo={serverInfo}
        serverOnline={serverOnline} />
      <Routes>
        <Route path="/" element={<HomePage
          serverInfo={serverInfo}
          setServerOnline={setServerOnline}
          setServerIp={setServerIp}
          serverIp={serverIp} />} />
        <Route path="/mapsettings" element={<ConfigPage
          setUploadMap={setUploadMap}
          setUploadConfigRooms={setUploadConfigRooms}
          serverInfo={serverInfo}
          setServerOnline={setServerOnline}
          setServerIp={setServerIp}
          serverIp={serverIp} />} />
        <Route path="/robotsettings" element={<RobotConfig
          setUploadRobotConfigurations={setUploadRobotConfigurations}
          setIsStage={setIsStage}
          serverInfo={serverInfo}
          setServerOnline={setServerOnline}
          setServerIp={setServerIp}
          serverIp={serverIp} />} />
        <Route path="/live" element={<Live
          uploadMap={uploadMap}
          uploadConfigRooms={uploadConfigRooms}
          uploadRobotConfigurations={uploadRobotConfigurations}
          serverInfo={serverInfo}
          serverOnline={serverOnline} />} />
      </Routes>
    </BrowserRouter>
  );
}

export default App;
