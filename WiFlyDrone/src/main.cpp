#include <Arduino.h>
#include "esp_camera.h"
#include "Network/WiFiLogins.h"
#include <WiFi.h>
#include "Camera/WebCam.h"

// Add IMU
// #include "Sensors/IMU.h"

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

  // Setup IMU
  setupIMU();

  // Setup Flight Controller
  setupController();

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
  delay(100);
  
  IMU_data = getIMU_vals();
  Serial.print("IMU roll: ");
  Serial.println(String(IMU_data[0], DEC));
  Serial.print("IMU pitch: ");
  Serial.println(String(IMU_data[1], DEC));
  Serial.print("IMU yaw: ");
  Serial.println(String(IMU_data[2], DEC));

  // Udate Measured Values
  roll.measured = IMU_data[0];
  pitch.measured = IMU_data[1];
  yaw.measured = IMU_data[2];

  // Stabilize Drone: TODO move to seperate thread
  stabilizeDrone();

  // Publish Debug Message
  chatter.publish( &str_msg );

  // Create Roll Pitch Yaw Message
  rpy_msg.header.frame_id = "/world";
  rpy_msg.header.stamp = nh.now();// timestamp
  rpy_msg.roll = IMU_data[0];// TODO: I have no idea if these are
  rpy_msg.pitch = IMU_data[1];// in the right locations
  rpy_msg.yaw = IMU_data[2];// Too lazy to check right now

  // Publish Roll, Pitch, Yaw message
  rpy.publish(&rpy_msg);

  // Test ROS
  testROS();
}
