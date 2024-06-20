#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <EEPROM.h>

#define AOUT_PIN A0   
int THRESHOLD;
#define THRESHOLD_EEPROM_ADDR 0

const char* ssid = ""; // Replace with your WiFi SSID
const char* password = ""; // Replace with your WiFi password

WiFiClient client;

void setup() {
  Serial.begin(9600);
  pinMode(D4, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  static unsigned long lastCheckTime = 0;
  unsigned long currentTime = millis();
  if (currentTime - lastCheckTime >= 1000) {
    sendMoistureData();
    lastCheckTime = currentTime;
  }
}

void sendMoistureData() {
  int value = analogRead(AOUT_PIN);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(client, "http://192.168.100.107:3000/moisture"); // Replace with your server endpoint

    http.addHeader("Content-Type", "application/json");

    String jsonData = "{\"controller_id\": 1, \"moisture\": " + String(value) + "}";
    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}
