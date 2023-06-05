const stageController = require('../controllers/stageController');
const express = require('express');
const router = express.Router();

router.route('/config')
    .get(stageController.getConfig);


module.exports = router;