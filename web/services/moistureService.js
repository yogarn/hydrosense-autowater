const pool = require("../database/database");

async function insertMoistureData(data) {
  const result = await pool.query('INSERT INTO moisture (controller_id, moisture) VALUES ($1, $2) RETURNING *', [data.controller_id, data.moisture]);
  return result.rows[0];
};

async function getAllMoistureData() {
  const result = await pool.query('SELECT * FROM moisture ORDER BY timestamp ASC LIMIT 10');
  return result.rows;
};

module.exports = {
  insertMoistureData,
  getAllMoistureData,
};
