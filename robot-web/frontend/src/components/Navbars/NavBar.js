import './NavBars.css'
import { Link } from 'react-router-dom'
import { useEffect } from 'react';


const NavBar = (props) => {

    const {uploadMap, uploadConfigRooms , uploadRobotConfigurations} = props;

    useEffect(() => {
        if(uploadMap === true && uploadConfigRooms === true && uploadRobotConfigurations === true){
            let liveDisplay = document.getElementById("liveDisplay");
            // removing the disabled class
            liveDisplay.classList.remove("disabled");
        }
    }, [uploadMap, uploadConfigRooms, uploadRobotConfigurations])
    return (
        <nav className="navbar navbar-expand-lg navbar-light bg-light navBar">
            <a className="navbar-brand" href="#">Terminator T-800</a>
            <button className="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
                <span className="navbar-toggler-icon"></span>
            </button>
            <div className="collapse navbar-collapse navBar" id="navbarNav">
                <ul className="navbar-nav">
                    <li className="nav-item">
                        <Link className="nav-link" to='/' >Home</Link>
                    </li>
                    <li className="nav-item">
                        <Link className="nav-link" to='/mapsettings'>Map Settings</Link>
                    </li>
                    <li className="nav-item">
                        <Link className="nav-link" to="/robotsettings">Robot Configuration</Link>
                    </li>
                    <li className="nav-item">
                        <Link className="nav-link disabled" id="liveDisplay" to="/live">Live Display</Link>
                    </li>
                </ul>
            </div>
        </nav>
    );
};

export default NavBar;