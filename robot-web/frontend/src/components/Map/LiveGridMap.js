import React, { useRef, useEffect, useState } from 'react';
import WebSocketClient from '../../services/WebSocketClient';
import './LiveGridMap.css'

const StageToMatrix = (x, y, scale, imgWidth, imgHeight) => {
  // converting the point to stage point
  const numOfBlockWidth = (imgWidth / 50);
  const numOfBlockHeight = (imgHeight / 40);
  const blockWidthHeight = (imgWidth / scale) / numOfBlockWidth;
  const blockWidthHeightPixel = (imgHeight / scale) / numOfBlockHeight;

  // Convert the stageX to pixel x-coordinate
  let pixel_x = (x + numOfBlockWidth / 2) * blockWidthHeightPixel;
  // Convert the stageY to pixel y-coordinate
  let pixel_y = ((numOfBlockHeight / 2) - y) * blockWidthHeightPixel;

  pixel_x = Math.round(pixel_x) + 4;
  pixel_y = Math.round(pixel_y) - 1;
  if(pixel_x < 0 || pixel_y < 0 || pixel_x > imgWidth || pixel_y > imgHeight) {
    return null;
  }
  return { x: pixel_x, y: pixel_y };
}


const LiveGridMap = (props) => {
  const { img, robotCurrentPosition } = props;
  const scale = 12;
  const [grid, setGrid] = useState([]);
  const [imgWidth, setImgWidth] = useState(0);
  const [imgHeight, setImgHeight] = useState(0);
  const [robotPosition, setRobotPosition] = useState(null);

  const gridRef = useRef(null);


  useEffect(() => {
    // adding the image to the canvas
    if (img) {
      gridRef.current.style.backgroundImage = `url(${img})`;
    } else {
      gridRef.current.style.backgroundImage = "";
      setGrid([]);
    }
  }, [img])

  useEffect(() => {
    // setting the robot position
    if (robotCurrentPosition) {
      let data = StageToMatrix(robotCurrentPosition.x, robotCurrentPosition.y, scale, imgWidth, imgHeight);
      console.log(data);
      if(data === null) {
        return;
      }
      if (robotPosition !== null) {
        setGrid(prevGrid => {
          const newGrid = [...prevGrid];
          newGrid[robotPosition.x] = [...newGrid[robotPosition.x]];
          newGrid[robotPosition.x][robotPosition.y] = { ...newGrid[robotPosition.x][robotPosition.y], robotPosition: false, color: "" };
          return newGrid;
        });
      }
      // setting the new robot position
      setGrid(prevGrid => {
        const newGrid = [...prevGrid];
        newGrid[data.x] = [...newGrid[data.x]];
        newGrid[data.x][data.y] = { ...newGrid[data.x][data.y], robotPosition: true, color: "green" };
        return newGrid;
      });
      setRobotPosition(data);
    }
  }, [robotCurrentPosition]);


  useEffect(() => {
    if(img === null) {
      setGrid([]);
      return;
    }
    const imgElement = new Image();
    imgElement.src = img;

    imgElement.onload = () => {
      const imgWidth = imgElement.width;
      const imgHeight = imgElement.height;

      setImgHeight(imgHeight);
      setImgWidth(imgWidth);

      const blockSize = scale; // Set the desired block size default (5px by 5px)

      const numBlocksX = Math.floor(imgWidth / blockSize);
      const numBlocksY = Math.floor(imgHeight / blockSize);

      let block = {
        robotPosition: false,
        path: false,
        color: "",
      }

      const newGrid = Array(numBlocksX).fill(Array(numBlocksY).fill(block));
      setGrid(newGrid);
    };
  }, [img]);



  return (
    <div className="grid-container-live"
      ref={gridRef}
      onContextMenu={(e) => { e.preventDefault(); }}>
      {grid.map((row, rowIndex) => (
        <div key={rowIndex} className="grid-row">
          {row.map((block, colIndex) => (
            <div
              key={colIndex}
              className={`grid-block-live`}
              style={block.color ? { backgroundColor: block.color } : {}}
            />
          ))}
        </div>
      ))}
    </div>
  );
};
export default LiveGridMap;
