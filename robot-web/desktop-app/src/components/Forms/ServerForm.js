import './ServerForm.css'
import post from '../../services/postServices';
import { useRef } from 'react';
import WebSocketClient from '../../services/WebSocketClient'
function ServerForm(props) {

    const { setServerOnline , setServerIp , serverIp} = props;
    const ipRef = useRef(null);
    const handleClick = async (event) => {
        event.preventDefault();
        const ip = ipRef.current.value;
        let res = await post.updateServerIP(ip);
        if(res === true) {
            alert("connected to the robot-server successfully");
            setServerIp(ip);
            setServerOnline(true);
        } else {
            alert(res);
            setServerIp(null);
            setServerOnline(false);
        }
    }

    return (
        <div>
            <h4 className="mt-4 item-center"><u>Robot Server Ip</u></h4>
            <form>
                <label htmlFor="ip">ip to connect</label>
                <input
                    type="text"
                    ref={ipRef}
                    id="ip"
                    className="form-control item"
                    value="ws://localhost:25197"
                />
                <button className="btn btn-danger item-center" onClick={handleClick}>UPDATE</button>
                {
                    serverIp !== null && (
                        <div>
                            <h5 className="mt-1 item-center green"><b><u>Current Server Ip</u></b></h5>
                            <h5 className="item-center green"><b>{serverIp}</b></h5>
                        </div>
                    )
                }
            </form>

        </div>
    )

}

export default ServerForm;