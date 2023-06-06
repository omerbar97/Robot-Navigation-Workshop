const serverController = require('../controllers/serverController.js');
const express = require('express');
const router = express.Router();

router.route('/ip')
    .get()
    .post(serverController.connectToServer);

module.exports = router;