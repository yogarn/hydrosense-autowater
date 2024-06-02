CREATE DATABASE hydrosense_autowater;

CREATE TABLE moisture (
    id SERIAL PRIMARY KEY,
    controller_id INT NOT NULL,
    moisture INT NOT NULL,
    timestamp TIMESTAMPTZ DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE controller (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    location VARCHAR(255)
);

ALTER TABLE moisture
ADD CONSTRAINT fk_controller
FOREIGN KEY (controller_id) REFERENCES controller(id);
