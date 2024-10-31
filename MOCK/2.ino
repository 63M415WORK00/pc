#include <WiFiS3.h>
#include <MQTTClient.h>
#include <R4HttpClient.h>

const char* ssid = "yamza";      
const char* password = "yaiyommy";  
WiFiSSLClient client;

R4HttpClient http;

const char MQTT_BROKER_ADRRESS[] = "phycom.it.kmitl.ac.th"; 
const int MQTT_PORT = 1883;                          
const char MQTT_CLIENT_ID[] = "66070114pat";    
const char MQTT_USERNAME[] = "";                          
const char MQTT_PASSWORD[] = "";                        

const char PUBLISH_TOPIC[] = "66070114/temp";  
const char SUBSCRIBE_TOPIC[] = "66070114/temp";

const int PUBLISH_INTERVAL = 5000;

unsigned long lastPublishTime = 0;

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

void setup() {
  Serial.begin(9600);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  connectToMQTT();
}

void loop() {
  mqtt.loop();

  int sensorValue = analogRead(A0);

  
  if (millis() - lastPublishTime > PUBLISH_INTERVAL) {
    sendToMQTT(sensorValue); 
    lastPublishTime = millis();
  }

  delay(1000);
}


void connectToMQTT() {
  mqtt.begin(MQTT_BROKER_ADRRESS, MQTT_PORT, network);

  mqtt.onMessage(messageHandler);

  Serial.print("Arduino UNO R4 - Connecting to MQTT broker");

  while (!mqtt.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  if (!mqtt.connected()) {
    Serial.println("Arduino UNO R4 - MQTT broker Timeout!");
    return;
  }

  if (mqtt.subscribe(SUBSCRIBE_TOPIC))
    Serial.print("Arduino UNO R4 - Subscribed to the topic: ");
  else
    Serial.print("Arduino UNO R4 - Failed to subscribe to the topic: ");

  Serial.println(SUBSCRIBE_TOPIC);
  Serial.println("Arduino UNO R4 - MQTT broker Connected!");
}

void sendToMQTT(int sensorValue) {
  char messageBuffer[10];
  dtostrf(sensorValue, 1, 2, messageBuffer);

  mqtt.publish(PUBLISH_TOPIC, messageBuffer);

  Serial.println("Arduino UNO R4 - sent to MQTT: topic: " + String(PUBLISH_TOPIC) + " | payload: " + String(messageBuffer));
}

void messageHandler(String& topic, String& payload) {
  Serial.println("Arduino UNO R4 - received from MQTT: topic: " + topic + " | payload: " + payload);
}
