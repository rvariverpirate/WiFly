#include <Arduino.h>
#include "esp_camera.h"
#include "Network/WiFiLogins.h"
#include <WiFi.h>
#include "Camera/WebCam.h"

// Add IMU
#include "Sensors/IMU.h"

// Include ROS and Messages
#include "ROS/ROS_Node.h"

// WiFi Credentials from Network/WiFiLogins.h
const char* ssid = MyNetwork.ssid;
const char* password = MyNetwork.password;

void setup(){

  // Setup Serial Communication at 115200 Baud Rate
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  // Setup Web Cam
  setupCamera();

  // Setup IMU
  setupIMU();

  // Setup WiFi Connection
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Setup ROS
  setupROS();

  // Start the Camera Server
  startCameraServer();
  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  printIMU();

  // Test ROS
  testROS();

}
