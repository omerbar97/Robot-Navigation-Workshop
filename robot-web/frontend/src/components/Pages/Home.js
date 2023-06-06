import NavBar from '../Navbars/NavBar';
import robotImg from '../../assets/robot.png';
import './Home.css'
import ServerForm from '../Forms/ServerForm';

function HomePage(props) {
    const { serverInfo , setServerOnline , setServerIp , serverIp} = props;

    return (
        <>
            <div className='row'>
                {
                    serverInfo === true && (
                        <div className='server-side mt-2'>
                            <ServerForm setServerOnline={setServerOnline} setServerIp={setServerIp} serverIp={serverIp}/>
                        </div>
                    )
                }

                <div className="home-page mt-2">
                    <h1>Welcome to the Robot Control Interface!</h1>
                    <p>
                        This website allows you to control a robot using the Player/Stage interface. You can set the robot's properties such as the map, IP address, and port to establish a connection.
                    </p>
                    <p>
                        Please implement the necessary functionality to control the robot and interact with the interface.
                    </p>
                    <div>
                        <img className="robotImg" src={robotImg}></img>
                    </div>
                </div>
            </div>

        </>
    );

}

export default HomePage;