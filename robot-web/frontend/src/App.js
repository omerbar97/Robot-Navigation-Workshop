import './App.css';
import { BrowserRouter, Route, Routes } from 'react-router-dom';
import { useEffect, useState } from 'react';
import ConfigPage from './components/Pages/Config';
import HomePage from './components/Pages/Home';
import RobotConfig from './components/Pages/RobotConfig';
import Live from './components/Pages/Live';
import NavBar from './components/Navbars/NavBar';

function App() {

  const [uploadMap, setUploadMap] = useState(false);
  const [uploadConfigRooms, setUploadConfigRooms] = useState(false);
  const [uploadRobotConfigurations, setUploadRobotConfigurations] = useState(false);
  const [serverInfo, setServerInfo] = useState(false);
  const [serverOnline , setServerOnline] = useState(false);
  const [serverIp, setServerIp] = useState(null);
  const [isStage, setIsStage] = useState(false);


  return (
    <BrowserRouter>
      <NavBar uploadMap={uploadMap}
        uploadConfigRooms={uploadConfigRooms}
        uploadRobotConfigurations={uploadRobotConfigurations} 
        setServerInfo={setServerInfo}
        serverInfo={serverInfo}
        serverOnline={serverOnline}/>
      <Routes>
        <Route path="/" element={<HomePage 
        serverInfo={serverInfo} 
        setServerOnline={setServerOnline} 
        setServerIp={setServerIp} 
        serverIp={serverIp}/>} />
        <Route path="/mapsettings" element={<ConfigPage 
        setUploadMap={setUploadMap} 
        setUploadConfigRooms={setUploadConfigRooms} 
        serverInfo={serverInfo} 
        setServerOnline={setServerOnline}
         setServerIp={setServerIp}
         serverIp={serverIp}/>} />
        <Route path="/robotsettings" element={<RobotConfig
         setUploadRobotConfigurations={setUploadRobotConfigurations}
          setIsStage={setIsStage} 
          serverInfo={serverInfo} 
          setServerOnline={setServerOnline}
           setServerIp={setServerIp}
           serverIp={serverIp}/>} />
        <Route path="/live" element={<Live uploadMap={uploadMap} uploadConfigRooms={uploadConfigRooms} uploadRobotConfigurations={uploadRobotConfigurations} serverInfo={serverInfo}/>}/>
      </Routes>
    </BrowserRouter>
  );
}

export default App;
