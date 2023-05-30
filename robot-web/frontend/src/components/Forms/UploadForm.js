import { useState, useEffect, useRef } from 'react'
import { CodeBlock, dracula } from 'react-code-blocks';
import post from '../../services/postServices';
import './UploadForm.css'

function UploadForm(props) {

    const { setUploadMap, setUploadConfigRooms } = props;

    const txtRef = useRef("");
    const mapRef = useRef(null);
    const [text, setText] = useState({ text: "" });
    const [map, setMap] = useState({ map: "" });

    const handleTxtChange = (event) => {
        event.preventDefault();
        if (event.target.files.length === 0) {
            setText({ text: "" });
            return;
        }
        const file = event.target.files[0];
        const reader = new FileReader();
        if (!file.type.match('text.*')) {
            alert("Please select text file only.");
            return;
        }
        reader.onload = function (event) {
            const fileContent = event.target.result; // Get the file content
            setText({ text: fileContent });
        }
        reader.readAsText(file);
    }

    const handleMapChange = (event) => {
        event.preventDefault();
        if (event.target.files.length === 0) {
            setMap({ map: "" });
            return;
        }
        const file = event.target.files[0];
        const reader = new FileReader();
        if (!file.type.match('image.*')) {
            alert("Please select image file only.");
            return;
        }
        reader.onload = function (event) {
            const fileContent = event.target.result; // Get the file content
            setMap({ map: fileContent });
        }
        reader.readAsDataURL(file);
    }

    const handleSubmit = async (event) => {
        // sending data to the server
        event.preventDefault();
        if (text.text === "" || map.map === "") {
            alert("please upload both files");
            return;
        }
        // sending the map to the server
        try {
            const request = await post.newMap(map);
            const request2 = await post.newRoomConfig(text);
            if (request.status === 200 && request2.status === 200) {
                setUploadMap(true);
                setUploadConfigRooms(true);
                alert("map and config files uploaded successfully");
            } else {
                alert("failed to upload map and config files");
            }
        } catch (error) {
            alert("failed to upload map and config files");
            console.log(error);
        }
    }

    return (
        <>
            <div className='form'>
                <div>
                    <h4><u>please upload the map file and the room config file.</u></h4>
                </div>
                <br />
                <div className="form-group">
                    <label htmlFor="imgToUpload">upload the map file</label>
                    <input
                        type="file"
                        ref={mapRef}
                        className="form-control item"
                        id="imgToUpload"
                        placeholder="map image"
                        onChange={handleMapChange}
                    />
                </div>
                <div className="form-group">
                    <label htmlFor="configFileToUpload">upload the room config file</label>
                    <input
                        type="file"
                        ref={txtRef}
                        className="form-control item"
                        id="configFileToUpload"
                        placeholder="config file"
                        onChange={handleTxtChange}
                    />
                </div>
                <button
                    className='btn btn-danger mb-2'
                    onClick={handleSubmit}>send to server</button>
                {
                    text.text !== "" && (
                        <CodeBlock
                            text={text.text}
                            className="codeBlockSection"
                            showLineNumbers={false}
                            theme={dracula}
                        />
                    )
                }

            </div>
        </>
    )
}

export default UploadForm;