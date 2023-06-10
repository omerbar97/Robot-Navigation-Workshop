const robotController = require('../controllers/robotController');
const express = require('express');
const router = express.Router();



router.route('/simulator')
    .post(robotController.postRobotSimulation);

// router.route('/physical')
//     .get()
//     .post();

router.route('/startStage')
    .post(robotController.startStage);

router.route('/startRobot')
    .post(robotController.startRobot)

router.route('/stop')
    .post(robotController.stopRobot);

router.route('/config')
    .get(robotController.Config);



module.exports = router;