// const net = require('net');

// const PORT = 8080;
// const HOST = 'localhost';

// const client = new net.Socket();

// client.connect(PORT, HOST, () => {
//   console.log('Connected to C++ server');

//   // Send data to the C++ server
//   const data = 'Hello from Node.js server';
// });



// client.on('data', (data) => {
//   console.log('Received from C++ server:', data.toString());
// });

// process.stdin.on('data', data => {
//   // clean up the input string
//   let t = data.toString().trim();
//   let jsonData = { text: t };
//   let jsonStr = JSON.stringify(jsonData);
//   console.log(jsonStr); // Print the JSON string for debugging
//   client.write(jsonStr);
// });

// client.on('close', () => {
//   console.log('Connection closed');
// });


// // Handle server errors
// client.on('error', (error) => {
//   console.error('Socket error:', error.message);
// });

const express = require('express');
const customEnv = require('custom-env');
const cors = require('cors');
const bodyParser = require('body-parser');
const mapRoute = require('./routes/map');
const robotRoute = require('./routes/robot');
const stageRoute = require('./routes/stage');

// setting the environment variables
customEnv.env(process.env.NODE_ENV, './config');
let ip = process.env.IP;
let port = process.env.PORT;

// creating the http server
const app = express();
app.use(cors());
app.use(express.json({ limit: '10mb' }));
app.use(express.urlencoded({ limit: '10mb', extended: true }));
app.use(express.Router())

// using static files
app.use(express.static('public'));

// setting the routes
app.use('/map', mapRoute);
app.use('/robot', robotRoute);
// app.use('/stage', stageRoute);


app.listen(port, ip, () => {
  console.log(`Server running at http://${ip}:${port}/`);
});
