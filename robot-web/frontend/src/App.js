import './App.css';
import { BrowserRouter, Route, Routes } from 'react-router-dom';
import ConfigPage from './components/Pages/Config';
import HomePage from './components/Pages/Home';
import RobotConfig from './components/Pages/RobotConfig';

function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<HomePage />} />
        <Route path="/mapsettings" element={<ConfigPage />} />
        <Route path="/robotsettings" element={<RobotConfig />} />
      </Routes>
    </BrowserRouter>
  );
}

export default App;
