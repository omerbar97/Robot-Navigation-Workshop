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
  const [isStage, setIsStage] = useState(false);


  return (
    <BrowserRouter>
      <NavBar uploadMap={uploadMap}
        uploadConfigRooms={uploadConfigRooms}
        uploadRobotConfigurations={uploadRobotConfigurations} />
      <Routes>
        <Route path="/" element={<HomePage />} />
        <Route path="/mapsettings" element={<ConfigPage setUploadMap={setUploadMap} setUploadConfigRooms={setUploadConfigRooms}/>} />
        <Route path="/robotsettings" element={<RobotConfig setUploadRobotConfigurations={setUploadRobotConfigurations} setIsStage={setIsStage}/>} />
        <Route path="/live" element={<Live uploadMap={uploadMap} uploadConfigRooms={uploadConfigRooms} uploadRobotConfigurations={uploadRobotConfigurations} />}/>
      </Routes>
    </BrowserRouter>
  );
}

export default App;
