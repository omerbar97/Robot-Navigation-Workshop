import './RobotStageForm.css'

function RobotStageForm() {


    return (
        <>
            <div className='form robotStageForm'>
                <div>
                    <h4><b>please make sure to upload all the necessary files for the stage program</b></h4>
                </div>
                <br />
                <div className="form-group d-flex">
                    <label className='col-3' htmlFor="imgToUpload">.world file</label>
                    <input
                        type="file"
                        className="form-control robotItemForm"
                        id="imgToUpload"
                        placeholder="map image"
                    />
                </div>
                <div className="form-group d-flex">
                    <label className='col-3' htmlFor="configFileToUpload">.cfg file</label>
                    <input
                        type="file"
                        className="form-control robotItemForm"
                        id="configFileToUpload"
                        placeholder="config file"
                    />
                </div>
                <div className="form-group d-flex">
                    <label className='col-3' htmlFor="robotIp">robot ip</label>
                    <input
                        type="text"
                        className="form-control item"
                        id="robotIp"
                        placeholder=""
                    />
                </div>
                <div className="form-group d-flex">
                    <label className='col-3' htmlFor="robotPort">robot port</label>
                    <input
                        type="text"
                        className="form-control item"
                        id="robotPort"
                        placeholder="default port is 6665"
                    />
                </div>
                <button className='btn btn-danger'>send to stage</button>
            </div>
        </>
    )
}

export default RobotStageForm;