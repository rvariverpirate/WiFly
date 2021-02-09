#include <ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Imu.h>
#include <rosserial_msgs/RPY.h>
#include <std_msgs/Empty.h>


// To use the TCP version of rosserial_arduino
#define ROSSERIAL_ARDUINO_TCP

// Set the rosserial socket server IP address
IPAddress server(192, 168, 1, 167); // Linux Box: 167, DeadBox: 215
// Always check this... especially when switching networks...
// Phone ROS Master IP: 192, 168, 238, 243 

// Set the rosserial socket server port
const uint16_t serverPort = 11411;

// Create Struct for Roll Pitch Yaw and Altitude as Doubles
typedef struct commandVals{
    float R;
    float P;
    float Y;
    float A;
}; 

// Create Global instace of Command Values
struct commandVals commandVals_g = {0, 0, 0, 0};

// ROS Setup
ros::NodeHandle  nh;

// Make Roll Pitch Yaw Publisher
rosserial_msgs::RPY rpy_msg;
ros::Publisher rpy("rpy", &rpy_msg);

// Create DEBUG Publisher for commandVals
rosserial_msgs::RPY command_vals_msg;
ros::Publisher command_vals_debug("command_vals_debug", &command_vals_msg);

// Make a RPY Command Callback
void rpy_command_callback(const rosserial_msgs::RPY& rpy_command){
  // Store message in global msg for availability
  commandVals_g.R = rpy_command.roll;// Sanity Check, commandVals_g are received properly here
  commandVals_g.P = rpy_command.pitch;
  commandVals_g.Y = rpy_command.yaw;
  commandVals_g.A = 0;//(double) rpy_command.Alt;
  //MC.debugPWM();
  /*Serial.print("Command roll: ");
  Serial.println(commandVals_g.R);
  Serial.print("Command pitch: ");
  Serial.println(commandVals_g.P);
  Serial.print("Command yaw: ");
  Serial.println(commandVals_g.Y);*/
};

// Create RPY Command Subscriber
ros::Subscriber<rosserial_msgs::RPY> rpy_command_sub("commands/rpy_command", &rpy_command_callback);

// Test publisher
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
char hello[13] = "hello world!";

void setupROS(){

  // Set the connection to rosserial socket server
  Serial.println("Setting up ROS");
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();

  // Another way to get IP
  Serial.print("IP = ");
  Serial.println(nh.getHardware()->getLocalIP());

  // Advertise Published Topics
  nh.advertise(chatter);
  nh.advertise(rpy);
  nh.advertise(command_vals_debug);

  // Subscribe to Topics
  nh.subscribe(rpy_command_sub);

  Serial.println("ROS Setup complete");

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