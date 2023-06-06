import { useEffect, useState } from 'react'
import { CodeBlock, dracula } from 'react-code-blocks';
import './RobotConfig.css'
import ServerForm from '../Forms/ServerForm';
import RobotStageForm from '../Forms/RobotStageForm';


function RobotConfig(props) {

    const { setUploadRobotConfigurations, setIsStage, serverInfo , setServerOnline , setServerIp , serverIp} = props;

    const [forStage, setForStage] = useState(null);

    const handleClickStage = (event) => {
        event.preventDefault();
        setForStage(true);
    }
    const handleClickPhysical = (event) => {
        event.preventDefault();
        setForStage(false);
    }

    return (
        <>
            {
                serverInfo === true && (
                    <div className='server-side mt-2'>
                        <ServerForm setServerOnline={setServerOnline} setServerIp={setServerIp} serverIp={serverIp}/>
                    </div>
                )
            }
            <div className='robot-page mt-2'>
                <div className='row'>
                    <div className='col-6'>
                        <button className='btn btn-danger'
                            onClick={handleClickStage}>set for stage</button>
                    </div>
                    <div className='col-6'>
                        <button
                            className='btn btn-warning'
                            onClick={handleClickPhysical}>set for ip</button>
                    </div>
                </div>
                <div className='row'>
                    {forStage && (
                        <div className='col-12'>
                            <RobotStageForm setUploadRobotConfigurations={setUploadRobotConfigurations} setIsStage={setIsStage} />
                        </div>
                    )}
                </div>
            </div>
        </>
    )
}

export default RobotConfig;