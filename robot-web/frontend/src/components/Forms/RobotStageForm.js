import './RobotStageForm.css'
import post from '../../services/postServices';
import { useState, useRef } from 'react';
function RobotStageForm(props) {

    const { setUploadRobotConfigurations, setIsStage } = props;

    const [worldFile, setWorldFile] = useState(null);
    const [configFile, setConfigFile] = useState(null);

    const ip = useRef(null);
    const port = useRef(null);

    const handleWorldFile = (event) => {
        // getting the file information
        if (event.target.files.length === 0) {
            setWorldFile(null);
            return;
        }
        const file = event.target.files[0];
        const reader = new FileReader();
        reader.onload = function () {
            const dataURL = reader.result;
            setWorldFile(dataURL);
        }
        reader.readAsDataURL(file);
    };

    const handleCfgFile = (event) => {
        // getting the file information
        if (event.target.files.length === 0) {
            setConfigFile(null);
            return;
        }
        const file = event.target.files[0];
        const reader = new FileReader();
        reader.onload = function () {
            const dataURL = reader.result;
            setConfigFile(dataURL);
        }
        reader.readAsDataURL(file);
    };


    const handleSend = async (event) => {
        event.preventDefault();

        // checking if the user uploaded all the necessary files
        if (worldFile === null || configFile === null || ip.current.value === "" || port.current.value === "") {
            alert("please upload all the necessary files");
            return;
        }

        // sending the data to the server
        const data = {
            world: worldFile,
            cfg: configFile,
            ip: ip.current.value,
            port: port.current.value,
        }
        console.log(data);

        // sending the data to the server
        const request = await post.newRobotSimulatorConfig(data);
        if (request && request.ok) {
            setIsStage(true);
            setUploadRobotConfigurations(true);
            alert("robot simulator config files was sent successfuly to server");
        }
        else {
            setUploadRobotConfigurations(false);
            alert("failed to send the config files to the server");
        }
    }

    return (
        <>
            <div className='form robotStageForm'>
                <div>
                    <h4><b>please make sure to upload all the necessary files for the stage program</b></h4>
                    <p>Make sure the map path inside the .world file is located at "/bitmaps/fromServer.png" otherwise it won't be able to start the stage!</p>

                </div>
                <br />
                <div className="form-group d-flex">
                    <label className='col-3' htmlFor="imgToUpload">.world file</label>
                    <input
                        type="file"
                        className="form-control robotItemForm"
                        id="imgToUpload"
                        placeholder="map image"
                        onChange={handleWorldFile}
                    />
                </div>
                <div className="form-group d-flex">
                    <label className='col-3' htmlFor="configFileToUpload">.cfg file</label>
                    <input
                        type="file"
                        className="form-control robotItemForm"
                        id="configFileToUpload"
                        placeholder="config file"
                        onChange={handleCfgFile}
                    />
                </div>
                <div className="form-group d-flex">
                    <label className='col-3' htmlFor="robotIp">robot ip</label>
                    <input
                        type="text"
                        ref={ip}
                        className="form-control item"
                        id="robotIp"
                        placeholder=""
                    />
                </div>
                <div className="form-group d-flex">
                    <label className='col-3' htmlFor="robotPort">robot port</label>
                    <input
                        type="text"
                        ref={port}
                        className="form-control item"
                        id="robotPort"
                        placeholder="default port is 6665"
                    />
                </div>
                <button className='btn btn-danger'
                    onClick={handleSend}>send to stage</button>
            </div>
        </>
    )
}

export default RobotStageForm;