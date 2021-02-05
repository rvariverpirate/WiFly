#include <PID_v1.h>
#include <pthread.h>
#include "../AHRS/AHRS.h"

struct PID_vals
{

  // Define The Gains
  double kP = 20;
  double kI = 1;
  double kD = 0;

  // Define the Setpoint, Input, and Output
  double desired = 0;// Desired Value
  double measured = 0;// Measured Value
  double U = 0;// Control Variable (Output)

};

// Create Instances of PID States
struct PID_vals roll;
struct PID_vals pitch;
struct PID_vals yaw;
struct PID_vals altitude;

// Create actual PID Loops
PID roll_PID(&roll.measured, &roll.U, &roll.desired, roll.kP, roll.kI, roll.kD, DIRECT);
PID pitch_PID(&pitch.measured, &pitch.U, &pitch.desired, pitch.kP, pitch.kI, pitch.kD, DIRECT);
PID yaw_PID(&yaw.measured, &yaw.U, &yaw.desired, yaw.kP, yaw.kI, yaw.kD, DIRECT);
PID altitude_PID(&altitude.measured, &altitude.U, &altitude.desired, altitude.kP, altitude.kI, altitude.kD, DIRECT);

// Create Global Time Delta
float deltat;


// Stabilize Drone: Caclualte PID's and Update PWM, run as seperate Thread
void *stabilizeDroneFusion(void *threadId){
    while(1){

      delay(10);
      // Serial.println("StabilizeDroneFusion:");

      // Get IMU Data and Perform Sensor Fusion
      updateAHRS();

      // Udate Measured Values
      roll.measured = AHRS.roll;
      pitch.measured = AHRS.pitch;
      yaw.measured = AHRS.yaw;

      // Update Control Vars by calculating the PID for RPY and Alt
      roll_PID.Compute();
      pitch_PID.Compute();
      yaw_PID.Compute();
      altitude_PID.Compute();

      // Get PID Outputs
      double U_A = altitude.U;
      double U_R = roll.U;
      double U_P = pitch.U;
      double U_Y = yaw.U;

      // TODO: Add Yaw to equation

      // Update PWM based on PID Outputs
      double pwm_RF = (U_A - U_R - U_P);// Right Front Motor
      double pwm_RB = (U_A - U_R + U_P);// Right Back Motor
      double pwm_LB = (U_A + U_R + U_P);// Left Back Motor
      double pwm_LF = (U_A + U_R - U_P);// Left Front Motor

      /*Serial.println("ROLL:");
      Serial.print(String(roll.desired, DEC));
      Serial.print(" ");
      Serial.print(String(roll.measured, DEC));
      Serial.print(" ");
      Serial.print(String(roll.U, DEC));
      Serial.print(" ");
      Serial.println(String(pwm_RF, DEC));*/
    }
}

/*
// Stabilize Drone: Caclualte PID's and Update PWM, run as seperate Thread
void *stabilizeDroneRAW(void *threadId){
    while(1){
        Serial.println("StabilizeDrone:");
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

        // Update Control Vars by calculating the PID for RPY and Alt
        roll_PID.Compute();
        pitch_PID.Compute();
        yaw_PID.Compute();
        altitude_PID.Compute();

        // Get PID Outputs
        double U_A = altitude.U;
        double U_R = roll.U;
        double U_P = pitch.U;
        double U_Y = yaw.U;

        // TODO: Add Yaw to equation

        // Update PWM based on PID Outputs
        double pwm_RF = (U_A - U_R - U_P);// Right Front Motor
        double pwm_RB = (U_A - U_R + U_P);// Right Back Motor
        double pwm_LB = (U_A + U_R + U_P);// Left Back Motor
        double pwm_LF = (U_A + U_R - U_P);// Left Front Motor

        Serial.println("ROLL:");
        Serial.print(String(roll.desired, DEC));
        Serial.print(" ");
        Serial.print(String(roll.measured, DEC));
        Serial.print(" ");
        Serial.print(String(roll.U, DEC));
        Serial.print(" ");
        Serial.println(String(pwm_RF, DEC));
    }
}
*/

void setupController(){
  Serial.println("Setting up Controller..");

  delay(100);

  // Turn on Control Loops
  roll_PID.SetMode(AUTOMATIC);
  pitch_PID.SetMode(AUTOMATIC);
  yaw_PID.SetMode(AUTOMATIC);
  altitude_PID.SetMode(AUTOMATIC);

  // Set output limits (only have 1 Byte of resolution on PWM)
  /*roll_PID.SetOutputLimits(0, 255);
  pitch_PID.SetOutputLimits(0, 255);
  yaw_PID.SetOutputLimits(0, 255);
  altitude_PID.SetOutputLimits(0, 255);*/

  // Put Controller Stabilization in its own Thread
  pthread_t stabilizer;
  int returnValue;
  returnValue = pthread_create(&stabilizer, NULL, stabilizeDroneFusion, (void *)1);

  if (returnValue) {
    Serial.println("An error has occurred");
    while(1);
  }

}

// Scale a Double from one range to another
double mapDouble(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}