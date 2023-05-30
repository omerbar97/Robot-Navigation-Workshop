import './NavBars.css'
import { Link } from 'react-router-dom'


const NavBar = () => {
    return (
        <nav className="navbar navbar-expand-lg navbar-light bg-light navBar">
            <a className="navbar-brand" href="#">Terminator T-800</a>
            <button className="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
                <span className="navbar-toggler-icon"></span>
            </button>
            <div className="collapse navbar-collapse" id="navbarNav">
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
                        <Link className="nav-link disabled">Live Display</Link>
                    </li>
                </ul>
            </div>
        </nav>
    );
};

export default NavBar;