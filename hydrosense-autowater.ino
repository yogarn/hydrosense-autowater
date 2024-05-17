#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

ESP8266WebServer server(80);

#define AOUT_PIN A0   
int THRESHOLD;

#define THRESHOLD_EEPROM_ADDR 0

void setup() {
  Serial.begin(9600);
  pinMode(D4, OUTPUT);

  WiFi.softAP("ESP8266_AP", "password123");
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  EEPROM.begin(512);
  EEPROM.get(THRESHOLD_EEPROM_ADDR, THRESHOLD);
  EEPROM.end();

  server.on("/", HTTP_GET, handleRoot);

  server.on("/moisture", HTTP_GET, handleMoisture);

  server.on("/updateThreshold", HTTP_POST, updateThreshold);

  server.begin();
}

void loop() {
  server.handleClient();
  
  static unsigned long lastCheckTime = 0;
  unsigned long currentTime = millis();
  if (currentTime - lastCheckTime >= 1000) {
    handleMoisture();
    lastCheckTime = currentTime;
  }
}


void handleRoot() {
  String content = "<html><head><script>function refreshData() {var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById('moistureLevel').innerHTML = this.responseText;}}; xhttp.open('GET', '/moisture', true); xhttp.send();} setInterval(refreshData, 500);</script></head><body>";
  content += "<h1>Soil Moisture Level</h1>";
  content += "<p id='moistureLevel'>Loading...</p>";
  
  content += "<form action='/updateThreshold' method='post'>";
  content += "Threshold: <input type='number' name='threshold' value='" + String(THRESHOLD) + "'><br>";
  content += "<input type='submit' value='Update Threshold'>";
  content += "</form>";

  content += "</body></html>";

  server.send(200, "text/html", content);
}

void handleMoisture() {
  int value = analogRead(AOUT_PIN);
  
  if (value > THRESHOLD) {
    digitalWrite(D4, LOW);
    server.send(200, "text/plain", "The soil is DRY (" + String(value) + ")");
  }
  else {
    digitalWrite(D4, HIGH);
    server.send(200, "text/plain", "The soil is WET (" + String(value) + ")");
  }
}

void updateThreshold() {
  if (server.hasArg("threshold")) {
    int newThreshold = server.arg("threshold").toInt();
    if (newThreshold >= 0 && newThreshold <= 1023) {
      THRESHOLD = newThreshold;
      
      EEPROM.begin(512);
      EEPROM.put(THRESHOLD_EEPROM_ADDR, THRESHOLD);
      EEPROM.commit();
      EEPROM.end();

      server.send(200, "text/plain", "Threshold updated successfully");
    } else {
      server.send(400, "text/plain", "Invalid threshold value");
    }
  } else {
    server.send(400, "text/plain", "No threshold value provided");
  }
}
