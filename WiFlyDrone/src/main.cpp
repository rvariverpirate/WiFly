#include <Arduino.h>
#include <EEPROM.h>
#include "esp_camera.h"
#include "Network/WiFiLogins.h"
#include <WiFi.h>
#include "Camera/WebCam.h"

// Include ROS and Messages
#include "ROS/ROS_Node.h"

// Include Flight Controller
#include "FlightController/Controller.h"

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

  // Setup AHRS: IMU Sensor Fusion
  setupAHRS();

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

  // Setup Flight Controller
  setupController();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);// TODO: Rrplace delays, they are killing your execution time

  // Create Roll Pitch Yaw Message
  rpy_msg.header.frame_id = "/world";
  rpy_msg.header.stamp = nh.now();// timestamp
  rpy_msg.roll = roll.measured;// TODO: I have no idea if these are
  rpy_msg.pitch = pitch.measured;// in the right locations
  rpy_msg.yaw = yaw.measured;// Too lazy to check right now

  // Publish Roll, Pitch, Yaw message
  rpy.publish(&rpy_msg);

  // Test ROS
  testROS();
}
