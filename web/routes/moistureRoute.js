const express = require('express');
const router = express.Router();
const { postMoistureData, getMoistureData } = require('../controllers/moistureController');

router.post('/moisture', postMoistureData);
router.get('/moisture', getMoistureData);

module.exports = router;
