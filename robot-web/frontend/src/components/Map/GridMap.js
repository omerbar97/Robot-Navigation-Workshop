import React, { useRef, useEffect, useState } from 'react';
import './GridMap.css'

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


const GridMap = (props) => {
  const { img, setExitRoom, setCenterRoom, setEnterRoom, id, scale } = props;
  const [grid, setGrid] = useState([]);
  const [imgWidth, setImgWidth] = useState(0);
  const [imgHeight, setImgHeight] = useState(0);

  const [centerGrid, setCenterGrid] = useState(null);
  const [enterGrid, setEnterGrid] = useState(null);
  const [exitGrid, setExitGrid] = useState(null);

  const gridRef = useRef(null);
  const zoomScale = useRef(1);
  const dragStart = useRef({ x: 0, y: 0 });
  const dragOffset = useRef({ x: 0, y: 0 });
  const isDragging = useRef(false);


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
  }, [img, scale]);

  // useEffect(() => {

  // })

  useEffect(() => {


  }, [grid])

  const handleClick = (rowIndex, colIndex) => {
    if (id === "center") {
      if (centerGrid !== null) {
        // Delete the previous center
        setGrid(prevGrid => {
          const newGrid = [...prevGrid];
          newGrid[centerGrid.rowIndex] = [...newGrid[centerGrid.rowIndex]];
          newGrid[centerGrid.rowIndex][centerGrid.colIndex] = { ...newGrid[centerGrid.rowIndex][centerGrid.colIndex], center: false, color: "" };
          return newGrid;
        });
      }
      // Setting the new center
      setGrid(prevGrid => {
        const newGrid = [...prevGrid];
        newGrid[rowIndex] = [...newGrid[rowIndex]];
        newGrid[rowIndex][colIndex] = { ...newGrid[rowIndex][colIndex], center: true, color: "green" };
        return newGrid;
      });
      let text = matrixToStage(rowIndex, colIndex, scale, imgWidth, imgHeight);
      setCenterRoom(text);
      setCenterGrid({ rowIndex, colIndex });
    } else if (id === "enter") {
      if (enterGrid !== null) {
        // Delete the previous enter
        setGrid(prevGrid => {
          const newGrid = [...prevGrid];
          newGrid[enterGrid.rowIndex] = [...newGrid[enterGrid.rowIndex]];
          newGrid[enterGrid.rowIndex][enterGrid.colIndex] = { ...newGrid[enterGrid.rowIndex][enterGrid.colIndex], enter: false, color: "" };
          return newGrid;
        });
      }
      // Setting the new enter
      setGrid(prevGrid => {
        const newGrid = [...prevGrid];
        newGrid[rowIndex] = [...newGrid[rowIndex]];
        newGrid[rowIndex][colIndex] = { ...newGrid[rowIndex][colIndex], enter: true, color: "blue" };
        return newGrid;
      });
      let text = matrixToStage(rowIndex, colIndex, scale, imgWidth, imgHeight);
      setEnterRoom(text);
      setEnterGrid({ rowIndex, colIndex });
    } else if (id === "exit") {
      if (exitGrid !== null) {
        // Delete the previous exit
        setGrid(prevGrid => {
          const newGrid = [...prevGrid];
          newGrid[exitGrid.rowIndex] = [...newGrid[exitGrid.rowIndex]];
          newGrid[exitGrid.rowIndex][exitGrid.colIndex] = { ...newGrid[exitGrid.rowIndex][exitGrid.colIndex], exit: false, color: "" };
          return newGrid;
        });
      }
      // Setting the new exit
      setGrid(prevGrid => {
        const newGrid = [...prevGrid];
        newGrid[rowIndex] = [...newGrid[rowIndex]];
        newGrid[rowIndex][colIndex] = { ...newGrid[rowIndex][colIndex], exit: true, color: "yellow" };
        return newGrid;
      });
      let text = matrixToStage(rowIndex, colIndex, scale, imgWidth, imgHeight);
      setExitRoom(text);
      setExitGrid({ rowIndex, colIndex });
    } else {
      return;
    }
  };


  const handleScroll = event => {
    event.preventDefault(); // Prevent the default scroll behavior

    const containerRect = gridRef.current.getBoundingClientRect();

    const containerX = event.clientX - containerRect.left; // Mouse X position relative to the container
    const containerY = event.clientY - containerRect.top; // Mouse Y position relative to the container

    const zoomStep = 0.05; // Set the zoom step value

    let zoomDelta = 0;

    if (event.deltaY > 0) {
      // Scrolling down, zoom out
      zoomDelta = -zoomStep;
    } else {
      // Scrolling up, zoom in
      zoomDelta = zoomStep;
    }

    // Calculate the scale factor based on the zoom delta
    const scaleFactor = Math.exp(zoomDelta);

    // Calculate the translation adjustment based on the mouse position
    const adjustmentX = containerX - containerX * scaleFactor;
    const adjustmentY = containerY - containerY * scaleFactor;

    // Apply the zoom scale and translation adjustment to the container
    const currentTransform = gridRef.current.style.transform;
    const newTransform = `scale(${zoomScale.current * scaleFactor})`;

    // Update the zoom scale and translation offset
    zoomScale.current *= scaleFactor;
    dragOffset.current.x += adjustmentX;
    dragOffset.current.y += adjustmentY;

    // Apply the transformation to the container with a transition for smoother animation
    gridRef.current.style.transform = newTransform;
    gridRef.current.style.transition = 'transform 0.2s';

    // Reset the transition property after the animation is complete
    setTimeout(() => {
      gridRef.current.style.transition = '';
    }, 200);
  };


  const handleMouseDown = event => {
    if (event.button === 2) {
      // Right mouse button is pressed, start dragging
      isDragging.current = true;
      dragStart.current.x = event.clientX;
      dragStart.current.y = event.clientY;
    }
  };

  const handleMouseMove = event => {
    if (isDragging.current) {
      // Calculate the distance moved
      const deltaX = event.clientX - dragStart.current.x;
      const deltaY = event.clientY - dragStart.current.y;

      // Update the drag offset
      dragOffset.current.x += deltaX;
      dragOffset.current.y += deltaY;

      // Apply the drag offset to the map container
      gridRef.current.style.transform = `scale(${zoomScale.current}) translate(${dragOffset.current.x}px, ${dragOffset.current.y}px)`;

      // Update the drag start position
      dragStart.current.x = event.clientX;
      dragStart.current.y = event.clientY;
    }
  };

  const handleMouseUp = () => {
    // Stop dragging
    isDragging.current = false;
  };

  for (let i = 0; i < grid.length; i++) {
    if (grid[i].center === true) {
      console.log("center is ")
      console.log(grid[i].center);
    }
    if (grid[i].enter === true) {
      console.log("enter is ")
      console.log(grid[i].enter);
    }
    if (grid[i].exit === true) {
      console.log("exit is ")
      console.log(grid[i].exit);
    }
  }
  return (
    <div className="grid-container"
      ref={gridRef}
      onMouseDown={handleMouseDown}
      onMouseMove={handleMouseMove}
      onMouseUp={handleMouseUp}
      onContextMenu={(e) => { e.preventDefault(); }}>
      {grid.map((row, rowIndex) => (
        <div key={rowIndex} className="grid-row">
          {row.map((block, colIndex) => (
            <div
              key={colIndex}
              className={`grid-block`}
              style={block.color ? { backgroundColor: block.color } : {}}
              onClick={() => handleClick(rowIndex, colIndex)}
            />
          ))}
        </div>
      ))}
    </div>
  );
};
export default GridMap;
