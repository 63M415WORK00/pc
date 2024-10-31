#include <WiFiS3.h>
#include <MQTTClient.h>
const char WIFI_SSID[] = "Alisala";          
const char WIFI_PASSWORD[] = "a.alisala";  
const char MQTT_BROKER_ADRRESS[] = "mqtt-dashboard.com"; 
const int MQTT_PORT = 1883;
const char MQTT_CLIENT_ID[] = "66070221-alisala-subscriber";  
const char SUBSCRIBE_TOPIC[] = "phycom";    
WiFiClient network;
MQTTClient mqtt = MQTTClient(256);
void setup() {
  Serial.begin(9600);
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    Serial.print("Connecting to SSID: ");
    Serial.println(WIFI_SSID);
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    delay(10000);
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  connectToMQTT();
}
void loop() {
  mqtt.loop();
}
void connectToMQTT() {
  mqtt.begin(MQTT_BROKER_ADRRESS, MQTT_PORT, network);
  mqtt.onMessage(messageHandler);
  Serial.print("Connecting to MQTT broker");
  while (!mqtt.connect(MQTT_CLIENT_ID)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  mqtt.subscribe(SUBSCRIBE_TOPIC);
  Serial.println("Subscribed to topic: " + String(SUBSCRIBE_TOPIC));
}
void messageHandler(String &topic, String &payload) {
  Serial.println("Received from MQTT: topic: " + topic + " | payload: " + payload);
  if (isNumeric(payload)) {
    int val = payload.toInt();
    if (val >= 0 && val <= 255) {
      analogWrite(9, val);
      Serial.println("Valid payload. LED value: " + String(val));
    } else {
      Serial.println("Invalid range. Value must be between 0 and 255.");
    }
  } else {
    Serial.println("Invalid payload. Non-numeric data received.");
  }
}


bool isNumeric(String str) {
  for (unsigned int i = 0; i < str.length(); i++) {
    if (!isDigit(str.charAt(i))) {
      return false;  // Return false if a non-digit character is found
    }
  }
  return true;
}
