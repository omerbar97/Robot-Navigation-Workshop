import { useState, useEffect, useRef } from "react";


const LiveGrid = ({ img }) => {
    const gridWidth = Math.ceil(img.width / 5);
    const gridHeight = Math.ceil(img.height / 5);
  
    const gridStyle = {
      gridTemplateColumns: `repeat(${gridWidth}, 5px)`,
      gridTemplateRows: `repeat(${gridHeight}, 5px)`,
      width: img.width,
      height: img.height,
    };
  
    const [gridCells, setGridCells] = useState(
      Array.from({ length: gridWidth * gridHeight }, () => ({
        current: false,
        path: false,
      }))
    );
  
    // const handleGridCellClick = (index) => {
    //   const updatedGridCells = [...gridCells];
    //   updatedGridCells[index].current = !updatedGridCells[index].current;
    //   setGridCells(updatedGridCells);
    // };
  
    // const handleGridCellHover = (index) => {
    //   const updatedGridCells = [...gridCells];
    //   updatedGridCells[index].hovered = true;
    //   setGridCells(updatedGridCells);
    // };
  
    // const handleGridCellLeave = (index) => {
    //   const updatedGridCells = [...gridCells];
    //   updatedGridCells[index].hovered = false;
    //   setGridCells(updatedGridCells);
    // };
  
    return (
      <div className="live-grid-container">
        <img src={img} alt="Grid Image" style={gridStyle} />
        <div className="grid-overlay" style={gridStyle}>
          {gridCells.map((cell, index) => (
            <div
              key={index}
              className={`grid-cell ${cell.current ? 'active' : ''} ${
                cell.hovered ? 'hovered' : ''
              }`}
            //   onClick={() => handleGridCellClick(index)}
            //   onMouseEnter={() => handleGridCellHover(index)}
            //   onMouseLeave={() => handleGridCellLeave(index)}
            />
          ))}
        </div>
      </div>
    );
  };
  
  
  
export default LiveGrid;