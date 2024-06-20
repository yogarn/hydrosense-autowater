# Hydrosense Autowater
Hydrosense Autowater is an IoT-based network sensor used to monitor moisture data in plant soil. This IoT device should be able to water plants automatically if they exceed a certain threshold. Users can also monitor the moisture value at the current time.  

## To-do
- [x] Realtime moisture monitoring from the website
- [ ] Automatic watering plants based on threshold
- [ ] Customizable threshold settings from the website

## Technology & Tools
- NodeMCU ESP8266
- Capacitive Soil Moisture Sensor
- 12V Water Pump
- Relay

## Setup & Installations
1. Clone or download this repository
2. Configure Wifi SSID, password and server endpoint in `hydrosense-autowater.ino`
3. Upload `hydrosense-autowater.ino` to ESP8266 using Arduino IDE
4. Run `npm install`
5. Configure the database settings in your `.env`
6. Run `web node/index.js`
