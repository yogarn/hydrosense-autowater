const { insertMoistureData, getAllMoistureData } = require('../services/moistureService');

const postMoistureData = async (req, res) => {
  const { controller_id, moisture } = req.body;
  try {
    if (controller_id == null || moisture == null) {
      throw new Error("controller_id and moisture cannot be null")
    }
    const data = await insertMoistureData({controller_id, moisture});
    req.io.emit('data', data);
    res.status(201).send(data);
  } catch (err) {
    console.error(err);
    res.status(500).send('Server error');
  }
};

const getMoistureData = async (req, res) => {
  try {
    const data = await getAllMoistureData();
    res.status(200).send(data);
  } catch (err) {
    console.error(err);
    res.status(500).send('Server error');
  }
};

module.exports = {
  postMoistureData,
  getMoistureData,
};
