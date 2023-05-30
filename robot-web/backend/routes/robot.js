const robotController = require('../controllers/mapController');
const express = require('express');
const router = express.Router();

router.route('/simulator')
    .get()
    .post();

router.route('/physical')
    .get()
    .post();

module.exports = router;