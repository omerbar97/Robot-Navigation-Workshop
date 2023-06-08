const robotController = require('../controllers/robotController');
const express = require('express');
const router = express.Router();



router.route('/simulator')
    .post(robotController.postRobotSimulation);

// router.route('/physical')
//     .get()
//     .post();

router.route('/start')
    .post(robotController.startRobot);



module.exports = router;