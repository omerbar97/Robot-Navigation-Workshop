const serverController = require('../controllers/serverController.js');
const express = require('express');
const router = express.Router();

router.route('/ip')
    .get()
    .post(serverController.connectToServer);

router.route('/')
    .get(serverController.oldFiles);

module.exports = router;