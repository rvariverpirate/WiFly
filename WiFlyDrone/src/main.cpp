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

// Setup Timers to Replace Delays
unsigned long rosTransmitTimer = millis();
unsigned long rosTransmitPeriod = 50;// (ms)

// Flag indicating Wether or not to Use Thread for Stabilization Loop
bool useThread = false;

// Primary Setup Method
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
  Serial.println("Connecting to WiFi");
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
  setupController(useThread);// Boolean indicates wther to use seperate thread or not
}

void loop() {
  unsigned long currentTime = millis();

  if(!useThread){
    stabilizeDroneFusion_2();
  }

  // Periodically Transmit Orientation data Back to ROS master
  // Note: Use non Thead Blocking timers instead of delay
  if(currentTime - rosTransmitTimer > rosTransmitPeriod) {

    Serial.println("");
    Serial.println("From main loop...");
    Serial.print("Roll: ");
    Serial.print(roll.measured);
    Serial.print(", Pitch: ");
    Serial.print(pitch.measured);
    Serial.print(", Yaw: ");
    Serial.println(yaw.measured);

    Serial.print("ax = ");  Serial.print((int)1000 * AHRS.ax);
    Serial.print(" ay = "); Serial.print((int)1000 * AHRS.ay);
    Serial.print(" az = "); Serial.print((int)1000 * AHRS.az);
    Serial.println(" mg");

    Serial.print("rate = ");
    Serial.print((float)AHRS.sumCount / AHRS.sum, 2);
    Serial.println(" Hz");
    Serial.print("AHRS.sumCount: "); Serial.println(AHRS.sumCount);
    Serial.print("AHRS.sum: "); Serial.println(AHRS.sum);

    // Create Roll Pitch Yaw Message
    rpy_msg.header.frame_id = "/world";
    rpy_msg.header.stamp = nh.now();// timestamp
    rpy_msg.roll = roll.measured;// TODO: I have no idea if these are
    rpy_msg.pitch = pitch.measured;// in the right locations
    rpy_msg.yaw = yaw.measured;// Too lazy to check right now

    // Publish Roll, Pitch, Yaw message
    rpy.publish(&rpy_msg);

    testROS();
    
    // Update Transmit Timer
    rosTransmitTimer = currentTime;
  }
}
