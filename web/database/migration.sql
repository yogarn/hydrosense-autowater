CREATE DATABASE hydrosense_autowater;

CREATE TABLE moisture (
    id SERIAL PRIMARY KEY,
    controller_id INT NOT NULL,
    moisture INT NOT NULL,
    timestamp TIMESTAMPTZ DEFAULT CURRENT_TIMESTAMP
);
