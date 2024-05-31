const pool = require("../database/database");

async function insertMoistureData(data) {
  const result = await pool.query(
    "INSERT INTO moisture (controller_id, moisture) VALUES ($1, $2) RETURNING *",
    [data.controller_id, data.moisture]
  );
  return result.rows[0];
}

async function getAllMoistureData() {
  const result = await pool.query(`
  SELECT * FROM (SELECT * FROM moisture ORDER BY timestamp DESC LIMIT 10)
  subquery ORDER BY timestamp ASC
  `);
  return result.rows;
}

module.exports = {
  insertMoistureData,
  getAllMoistureData,
};
