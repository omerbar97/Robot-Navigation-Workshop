const mapController = require('../controllers/mapController');
const express = require('express');
const router = express.Router();

router.route('/')
    .get(mapController.getMap)
    .post(mapController.postMap);

router.route('/rooms')
    .get()
    .post(mapController.postRooms);

module.exports = router;