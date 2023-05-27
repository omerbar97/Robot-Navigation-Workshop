const net = require('net');

const PORT = 8080;
const HOST = 'localhost';

const client = new net.Socket();

client.connect(PORT, HOST, () => {
  console.log('Connected to C++ server');

  // Send data to the C++ server
  const data = 'Hello from Node.js server';
});



client.on('data', (data) => {
  console.log('Received from C++ server:', data.toString());
});

process.stdin.on('data', data => {
  // clean up the input string
  let t = data.toString().trim();
  let jsonData = { text: t };
  let jsonStr = JSON.stringify(jsonData);
  console.log(jsonStr); // Print the JSON string for debugging
  client.write(jsonStr);
});

client.on('close', () => {
  console.log('Connection closed');
});


// Handle server errors
client.on('error', (error) => {
  console.error('Socket error:', error.message);
});