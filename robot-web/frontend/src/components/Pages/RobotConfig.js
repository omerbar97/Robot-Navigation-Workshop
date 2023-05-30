import { useEffect, useState } from 'react'
import { CodeBlock, dracula } from 'react-code-blocks';
import './RobotConfig.css'
import NavBar from '../Navbars/NavBar';
import RobotStageForm from '../Forms/RobotStageForm';


function RobotConfig() {

    const [forStage , setForStage] = useState(null);

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
        <NavBar/>   
        <div className='robot-page'>
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
                        <RobotStageForm/>
                    </div>
                )}
            </div>
        </div>
        </>
    )
}

export default RobotConfig;