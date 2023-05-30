import './ConfigForm.css'
import { CodeBlock, dracula } from "react-code-blocks";
import { useEffect, useRef, useState } from 'react';
import post from '../../services/postServices';
function ConfigForm(props) {

    const { setImg,
        centerRoom,
        enterRoom,
        exitRoom,
        setId,
        img,
        setScale,
        setUploadMap,
        setUploadConfigRooms } = props;

    const [text, setText] = useState({
        text: "",
    });

    useEffect(() => {
        if (text.text !== "") {
            // disabling the button
            document.getElementById("selectScale").disabled = true;
        }
    }, [text])
    const nameRef = useRef(null);
    const roomIdRef = useRef(null);

    const handleImg = (event) => {
        event.preventDefault();
        if (event.target.files.length === 0) {
            setImg(null);
            return;
        }
        const file = event.target.files[0];
        const reader = new FileReader();
        if (!file.type.match('image.*')) {
            alert("Please select image only.");
            return;
        }
        reader.onload = function () {
            const dataURL = reader.result;
            setImg(dataURL);
        }
        reader.readAsDataURL(file);
    }


    const handleBtnPress = (event) => {
        event.preventDefault();
        // getting the id of the button
        const id = event.target.id;
        setId(id);
    }

    const handleSubmit = (event) => {
        event.preventDefault();
        // adding to the text argument the center room , enter room and exit room
        let data = {
            text: text.text + nameRef.current.value + " " + roomIdRef.current.value + " " + centerRoom + " " + enterRoom + " " + exitRoom + "\n",
        }
        setText(data);
    }

    const handleScale = (event) => {
        event.preventDefault();
        setScale(event.target.value);
    }

    const sendConfigToServer = async (event) => {
        event.preventDefault();
        // sending the config file to the server
        const request = await post.newRoomConfig(text);
        if (request.status === 200) {
            setUploadConfigRooms(true);
            alert("config file sent successfully");
        } else {
            alert("error sending config file");
        }
    }

    const sendMapToServer = async (event) => {
        event.preventDefault();
        // sending the config file to the server
        const request = await post.newMap({ map: img });
        if (request && request.status === 200) {
            setUploadMap(true);
            alert("map file sent successfully");
        } else {
            alert("error sending map file");
        }
    }

    return (
        <form className="form scrollContainer config-form config-page">
            <label htmlFor="selectScale"><b>grid scale </b></label>
            <select className="form-select form-select-sm"
                onChange={handleScale}
                id="selectScale">
                <option value="2">2</option>
                <option value="3">3</option>
                <option selected="5">5</option>
                <option value="7">7</option>
                <option value="10">10</option>
            </select>
            <div className="form-group d-flex">
                <input
                    type="file"
                    className="form-control item"
                    id="img"
                    placeholder="map image"
                    onChange={handleImg}
                />
                {img && (
                    <div className="form-group col-7">
                        <button className='btn btn-danger'
                            onClick={sendMapToServer}>send map to robot</button>
                    </div>
                )}
            </div>
            <div className="form-group">
                <input
                    type="text"
                    ref={nameRef}
                    className="form-control item"
                    id="name"
                    placeholder="room name"
                />
            </div>
            <div className="form-group">
                <input
                    type="text"
                    ref={roomIdRef}
                    className="form-control item"
                    id="roomId"
                    placeholder="room id"
                />
            </div>
            <div className='points'>
                <div className="form-group">
                    <input
                        type="text"
                        value={centerRoom}
                        className="form-control item"
                        id="centerRoom"
                        placeholder="center room"
                        disabled
                    />
                    <button className='btn btn-success mb-3'
                        id="center"
                        onClick={handleBtnPress}>SET CENTER ROOM</button>
                </div>
                <div className="form-group">
                    <input
                        type="text"
                        value={enterRoom}
                        className="form-control item"
                        id="enterRoom"
                        placeholder="enter room"
                        disabled
                    />
                    <button className='btn btn-info mb-3' id="enter" onClick={handleBtnPress}>SET ENTER ROOM</button>
                </div>
                <div className="form-group">
                    <input
                        type="text"
                        value={exitRoom}
                        className="form-control item"
                        id="exitRoom"
                        placeholder="exit room"
                        disabled
                    />
                    <button className='btn btn-warning mb-3' id="exit" onClick={handleBtnPress}>SET EXIT ROOM</button>

                </div>
                <div className="form-group">
                    <div className='row'>
                        <div className='col-4'>
                            <button
                                type="button"
                                className="btn btn-primary create-account"
                                onClick={handleSubmit}>
                                add room
                            </button>
                        </div>
                        <div className='col-8'>
                            <button
                                type="button"
                                className="btn btn-danger create-account"
                                onClick={sendConfigToServer}>
                                send config file to server
                            </button>
                        </div>
                    </div>

                </div>
                {
                    text.text !== "" && (
                        <CodeBlock
                            text={text.text}
                            className="configSection"
                            showLineNumbers={false}
                            theme={dracula}
                        />
                    )
                }

            </div>
        </form>

    )
}

export default ConfigForm