
const express = require('express');
const wsClient = require('./services/WebSocketClient');
const customEnv = require('custom-env');
const cors = require('cors');
const bodyParser = require('body-parser');
const mapRoute = require('./routes/map');
const robotRoute = require('./routes/robot');
const stageRoute = require('./routes/stage');
const serverRoute = require('./routes/server');

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
app.use('/stage', stageRoute);
app.use('/server', serverRoute);

app.listen(port, ip, () => {
  console.log(`Server running at http://${ip}:${port}/`);
});
