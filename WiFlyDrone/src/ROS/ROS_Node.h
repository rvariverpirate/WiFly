#include <ros.h>
#include <std_msgs/String.h>

// To use the TCP version of rosserial_arduino
#define ROSSERIAL_ARDUINO_TCP

// Set the rosserial socket server IP address
IPAddress server(192, 168, 1, 215); // Linux Box: 167;

// Set the rosserial socket server port
const uint16_t serverPort = 11411;

// ROS Setup
ros::NodeHandle  nh;

// Test publisher
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
char hello[13] = "hello world!";

void setupROS(){
  // Set the connection to rosserial socket server
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();

  // Another way to get IP
  Serial.print("IP = ");
  Serial.println(nh.getHardware()->getLocalIP());

  // Start to be polite
  nh.advertise(chatter);
}

void testROS(){
    // Publish ROS Message
    if (nh.connected()) {
        Serial.println("Connected");
        // Say hello
        str_msg.data = hello;
        chatter.publish( &str_msg );
    } else {
        Serial.println("Not Connected");
    }
    nh.spinOnce();
}