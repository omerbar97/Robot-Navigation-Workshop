import './Live.css';
import get from '../../services/getServices';
import LiveGrid from '../Map/LiveGrid';
import { useEffect, useState } from 'react';

async function getImgFromServer(setImg) {
    let res = await get.Map();
    if (res === null) {
        // failed to retrive the map
        alert("failed to retrive the map, try again later");
        return;
    }
    console.log(res);
    setImg(res);
}


function Live() {

    const [isLive, setIsLive] = useState(false);
    const [img, setImg] = useState(null); // the map image
    const handleBtn = (event) => {
        event.preventDefault();
        if(img === null){
            alert("problem with loading the map from the server, try again later")
            return;
        }
        setIsLive(!isLive);
    }

    useEffect(() => {
        if (isLive) {
            // getting the map from the server
            getImgFromServer(setImg);
        }
    }, [])

    return (
        <div className="conatiner live-page mt-5">
            <h5>
                <u>This is the live broadcast page, from here you can see the robot's movements in real time.</u>
            </h5>
            <div className="row"> {
                !isLive && (
                    <div className='col-6 right'>
                        <button
                            className='btn btn-warning'
                            onClick={handleBtn}>start robot</button>
                    </div>
                )
            }
                {
                    isLive && img && (
                        <div className='col-6 right'>
                            <button
                                className='btn btn-danger'
                                onClick={handleBtn}>stop robot</button>
                        </div>
                    )
                }
            </div>
            {isLive && img && (<div className='d-flex'>
                <div className='col-8'>
                    {/* here the map going to be */}
                    <LiveGrid img={img} />
                </div>
                <div className='col-4'>
                    <h2><b><u>Robot Live Data</u></b></h2>
                </div>
            </div>

            )}
        </div>
    );
}

export default Live;