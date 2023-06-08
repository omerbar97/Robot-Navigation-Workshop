import React, { useRef, useEffect, useState } from 'react';
import './LiveGridMap.css'

const matrixToStage = (x, y, scale, imgWidth, imgHeight) => {
  // converting the point to stage point
  const numOfBlockWidth = (imgWidth / 50);
  const numOfBlockHeight = (imgHeight / 40);
  const blockWidthHeight = (imgWidth / scale) / numOfBlockWidth;
  const blockWidthHeightPixel = (imgHeight / scale) / numOfBlockHeight;

  // Convert the pixel x-coordinate to stage coordinate
  let xStage = (numOfBlockWidth / 2 * blockWidthHeight - x) / -blockWidthHeight;
  // Convert the pixel y-coordinate to stage coordinate
  let yStage = (numOfBlockHeight / 2 * blockWidthHeightPixel - y) / blockWidthHeightPixel;

  // modifing the number only 2 digit after the decimal
  xStage = xStage * 100;
  xStage = Math.round(xStage);
  xStage = xStage / 100;

  yStage = yStage * 100;
  yStage = Math.round(yStage);
  yStage = yStage / 100;

  return xStage + " " + yStage;
}


const LiveGridMap = (props) => {
  const { img } = props;
  const scale = 12;
  const [grid, setGrid] = useState([]);
  const [imgWidth, setImgWidth] = useState(0);
  const [imgHeight, setImgHeight] = useState(0);

  const gridRef = useRef(null);
  const zoomScale = useRef(1);


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
        center: false,
        enter: false,
        exit: false,
      }

      const newGrid = Array(numBlocksX).fill(Array(numBlocksY).fill(block));
      setGrid(newGrid);
    };
  }, [img]);

  // useEffect(() => {

  // })

  useEffect(() => {


  }, [grid])


//   const handleScroll = event => {
//     event.preventDefault(); // Prevent the default scroll behavior

//     const containerRect = gridRef.current.getBoundingClientRect();

//     const containerX = event.clientX - containerRect.left; // Mouse X position relative to the container
//     const containerY = event.clientY - containerRect.top; // Mouse Y position relative to the container

//     const zoomStep = 0.05; // Set the zoom step value

//     let zoomDelta = 0;

//     if (event.deltaY > 0) {
//       // Scrolling down, zoom out
//       zoomDelta = -zoomStep;
//     } else {
//       // Scrolling up, zoom in
//       zoomDelta = zoomStep;
//     }

//     // Calculate the scale factor based on the zoom delta
//     const scaleFactor = Math.exp(zoomDelta);

//     // Calculate the translation adjustment based on the mouse position
//     const adjustmentX = containerX - containerX * scaleFactor;
//     const adjustmentY = containerY - containerY * scaleFactor;

//     // Apply the zoom scale and translation adjustment to the container
//     const currentTransform = gridRef.current.style.transform;
//     const newTransform = `scale(${zoomScale.current * scaleFactor})`;

//     // Update the zoom scale and translation offset
//     zoomScale.current *= scaleFactor;
//     dragOffset.current.x += adjustmentX;
//     dragOffset.current.y += adjustmentY;

//     // Apply the transformation to the container with a transition for smoother animation
//     gridRef.current.style.transform = newTransform;
//     gridRef.current.style.transition = 'transform 0.2s';

//     // Reset the transition property after the animation is complete
//     setTimeout(() => {
//       gridRef.current.style.transition = '';
//     }, 200);
//   };


//   const handleMouseDown = event => {
//     if (event.button === 2) {
//       // Right mouse button is pressed, start dragging
//       isDragging.current = true;
//       dragStart.current.x = event.clientX;
//       dragStart.current.y = event.clientY;
//     }
//   };

//   const handleMouseMove = event => {
//     if (isDragging.current) {
//       // Calculate the distance moved
//       const deltaX = event.clientX - dragStart.current.x;
//       const deltaY = event.clientY - dragStart.current.y;

//       // Update the drag offset
//       dragOffset.current.x += deltaX;
//       dragOffset.current.y += deltaY;

//       // Apply the drag offset to the map container
//       gridRef.current.style.transform = `scale(${zoomScale.current}) translate(${dragOffset.current.x}px, ${dragOffset.current.y}px)`;

//       // Update the drag start position
//       dragStart.current.x = event.clientX;
//       dragStart.current.y = event.clientY;
//     }
//   };

//   const handleMouseUp = () => {
//     // Stop dragging
//     isDragging.current = false;
//   };


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
