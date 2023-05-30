import NavBar from '../Navbars/NavBar';
import './Home.css'

function HomePage() {


    return (
        <>
            <NavBar></NavBar>
            <div className="home-page mt-5">
                <h1>Welcome to the Robot Control Interface!</h1>
                <p>
                    This website allows you to control a robot using the Player/Stage interface. You can set the robot's properties such as the map, IP address, and port to establish a connection.
                </p>
                <p>
                    Please implement the necessary functionality to control the robot and interact with the interface.
                </p>
            </div>
        </>
    );

}

export default HomePage;