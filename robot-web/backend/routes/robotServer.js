const { startWsServer } = require('../controllers/robotServerController');
const express = require('express');
const router = express.Router();

router.route('/')
    .get()
    .post(startWsServer);

module.exports = router;