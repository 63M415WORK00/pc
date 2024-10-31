#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
struct Information {
    char name[61];
    char surname[61];
    char sex[5];
    int age;
    char id[13];
    double gpa;
};
 
void bubbleSort(struct Information students[], int count, char* condition) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int swap = 0;
            if ((strcasecmp(condition, "name") == 0 && strcasecmp(students[j].name, students[j + 1].name) > 0) || (strcasecmp(condition, "surname") == 0 && 
            strcasecmp(students[j].surname, students[j + 1].surname) > 0) || (strcasecmp(condition, "id") == 0 && strcasecmp(students[j].id, students[j + 1].id) > 0)){
                swap = 1;
            } 
            if (swap) {
                struct Information temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}
 
int main() {
    struct Information students[20];
    char check[14];
    for (int i = 0; i < 20; i++) {
        scanf("%s %s %s %d %s %lf", students[i].name, students[i].surname, students[i].sex, &students[i].age, students[i].id, &students[i].gpa);
    }
 
    scanf("%s", check);
    bubbleSort(students, 20, check);
 
    for (int i = 0; i < 20; i++) {
        if (strcmp(students[i].sex, "Male") == 0) {
            printf("Mr %c %s (%d) ID: %s GPA %.2lf\n", students[i].name[0], students[i].surname, students[i].age, students[i].id, students[i].gpa);
        } else {
            printf("Miss %c %s (%d) ID: %s GPA %.2lf\n", students[i].name[0], students[i].surname, students[i].age, students[i].id, students[i].gpa);
        }
    }
    return 0;
}
phufa — วันนี้ เวลา 3:53
#include <WiFiS3.h>
#include <MQTTClient.h>
#include <R4HttpClient.h>

const char* ssid = "า";      
const char* password = "12345678";  
ขยาย
message.txt
4 KB
﻿
#include <WiFiS3.h>
#include <MQTTClient.h>
#include <R4HttpClient.h>

const char* ssid = "า";      
const char* password = "12345678";  
WiFiSSLClient client;

R4HttpClient http;

const char MQTT_BROKER_ADRRESS[] = "phycom.it.kmitl.ac.th"; 
const int MQTT_PORT = 1883;                          
const char MQTT_CLIENT_ID[] = "66070161za";    
const char MQTT_USERNAME[] = "";                          
const char MQTT_PASSWORD[] = "";                        

const char PUBLISH_TOPIC[] = "66070161/food";  
const char SUBSCRIBE_TOPIC[] = "66070161/food";

const int PUBLISH_INTERVAL = 5000;

unsigned long lastPublishTime = 0;

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

const int trigPin = 9;
const int echoPin = 10;
long duration;
int distanceCm, distanceInch, check;

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

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  mqtt.loop();
  
  // int sensorValue = analogRead(A0);
  // float voltage = sensorValue * (5.0 / 1023.0); // Convert ADC value to voltage (assuming 5V reference)
  // float temperatureC = (voltage - 0.5) * 100.0; // Adjust for TMP36 offset, 10mV per °C

  // Serial.print("Temperature: ");
  // Serial.print(temperatureC);
  // Serial.println(" C");

  // Clear the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Set the trigPin HIGH for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Read the echoPin, return the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculate the distance in cm and inches
    distanceCm = duration * 0.034 / 2;
    distanceInch = duration * 0.0133 / 2;

    // Print the distances to the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distanceCm);
    Serial.println(" cm");
  
  if (millis() - lastPublishTime > PUBLISH_INTERVAL) {
    sendToMQTT(distanceCm); 
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

void sendToMQTT(int distanceCm) {
  char messageBuffer[10];
  if (distanceCm > 20) {
    strcpy(messageBuffer, "off");
  } else {
    dtostrf(distanceCm, 1, 2, messageBuffer);
  }

  mqtt.publish(PUBLISH_TOPIC, messageBuffer);

  Serial.println("Arduino UNO R4 - sent to MQTT: topic: " + String(PUBLISH_TOPIC) + " | payload: " + String(messageBuffer));
}

void messageHandler(String& topic, String& payload) {
  Serial.println("Arduino UNO R4 - received from MQTT: topic: " + topic + " | payload: " + payload);
}
