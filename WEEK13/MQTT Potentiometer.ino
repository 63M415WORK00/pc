#include <WiFiS3.h>
#include <MQTTClient.h>

const char WIFI_SSID[] = "Alisala";          
const char WIFI_PASSWORD[] = "a.alisala";  

const char MQTT_BROKER_ADRRESS[] = "mqtt-dashboard.com";  
const int MQTT_PORT = 1883;
const char MQTT_CLIENT_ID[] = "66070221-alisala-publisher";  
const char PUBLISH_TOPIC[] = "phycom";    

const int PUBLISH_INTERVAL = 1000;  // 1 second

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

unsigned long lastPublishTime = 0;

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

  if (millis() - lastPublishTime > PUBLISH_INTERVAL) {
    sendToMQTT();
    lastPublishTime = millis();
  }
}

void connectToMQTT() {
  mqtt.begin(MQTT_BROKER_ADRRESS, MQTT_PORT, network);
  mqtt.onMessage(messageHandler);

  Serial.print("Connecting to MQTT broker");

  while (!mqtt.connect(MQTT_CLIENT_ID)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  Serial.println("Connected to MQTT broker!");
}

void sendToMQTT() {
  int val = analogRead(A0);  // Read the potentiometer value (0-1023)
  val = map(val, 0, 1023, 0, 255);  // Scale the value to 0-255

  String val_str = String(val);

  char messageBuffer[10];
  val_str.toCharArray(messageBuffer, 10);

  mqtt.publish(PUBLISH_TOPIC, messageBuffer);
  Serial.println("Published to MQTT: " + String(messageBuffer));
}

void messageHandler(String &topic, String &payload) {
  // Not needed in the publishing code
}
