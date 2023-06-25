import robotImg from '../../assets/robot.png';
import './Home.css'
import ServerForm from '../Forms/ServerForm';
import { useEffect, useState } from 'react';
import { exec } from 'child_process';
import path from 'path';
import { chdir } from 'process';

function HomePage(props) {
    const { serverInfo, setServerOnline, setServerIp, serverIp } = props;
    const [robotProcess, setRobotProcess] = useState(false);
    const [robotProcessOnline, setRobotProcessOnline] = useState(false);
    const [port, setPort] = useState(0);

    const getRelativePath = (relativePath) => {
        // Get the current location of the component file
        const componentPath = __dirname; // This gives the absolute path of the current file

        // Calculate the relative path based on the component file location
        const resolvedPath = path.resolve(componentPath, relativePath);
        return resolvedPath;
    };

    // const generatePort = () => {
    //     const min = 10000;
    //     const max = 65535;
    //     return Math.floor(Math.random() * (max - min + 1)) + min;
    // };

    useEffect(() => {
        if (port !== 0) {
            alert('Robot process started on port: ' + port);
        }
    }, [port]);

    const handleClick = () => {

        let portServer = 25197;
        // const projectPath = '../../robot-client/cmake-build-debug/Server';
        const args = ['localhost', portServer];
        console.log(__dirname);
        if (robotProcessOnline === false) {
            // change the path to the project path
            chdir('../../robot-client/cmake-build-debug/');
            exec(`./Server ${args.join(' ')}`, (error, stdout, stderr) => {
                if (error) {
                    console.error(`Error executing command: ${error.message}`);
                    return;
                }
                if (stderr) {
                    console.error(`Command execution error: ${stderr}`);
                    return;
                }
            });

            setRobotProcess(robotProcess);
            setRobotProcessOnline(true);
            setPort(portServer);
        } else {
            alert('Robot process already started on port: ' + port);
        }
    }

    return (
        <>
            <div className='row d-flex'>
                {
                    serverInfo === true && (
                        <div className='server-side mt-2'>
                            <ServerForm setServerOnline={setServerOnline} setServerIp={setServerIp} serverIp={serverIp} />
                        </div>
                    )
                }
                <div className='btn btn-info exeBtn' onClick={handleClick}>
                    START ROBOT PROCESS SERVER (LOCALHOST)
                </div>
                <div className="home-page mt-2">
                    <h1>Welcome to the Robot Control Interface!</h1>
                    <p>
                        This app allows you to control a robot using the Player/Stage interface. You can set the robot's properties such as the map, IP address, and port to establish a connection.
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