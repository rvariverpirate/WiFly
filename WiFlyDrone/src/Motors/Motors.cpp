#include "Motors.h"
// This file will contain the motor pinout mapping
// and final PWM actuation

// TODO: Use actual pin mapping

/*
GPIO    Transistor  Motor
12      1           A
4       3           B
2       4           C
14      2           D
*/

// Constructor
Motors::Motors()
{
    setupMotors();
}

// Define motors as outputs and setup for PWM
void Motors::setupMotors()
{
    // Define PWM Channels, Frequency, and Resolution
    ledcSetup(ChannelA, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(ChannelB, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(ChannelB, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(ChannelB, PWM_FREQ, PWM_RESOLUTION);

    // Associate each PWM channel with a GPIO pin
    ledcAttachPin(MotorA, ChannelA);
    ledcAttachPin(MotorB, ChannelB);
    ledcAttachPin(MotorC, ChannelC);
    ledcAttachPin(MotorD, ChannelD);
};

void Motors::updateMotors(double dutyCycleA, double dutyCycleB, double dutyCycleC, double dutyCycleD)
{
    Serial.println("TODO: assign correct PWM to each motor");
    ledcWrite(ChannelA, dutyCycleA);
    ledcWrite(ChannelB, dutyCycleB);
    ledcWrite(ChannelC, dutyCycleC);
    ledcWrite(ChannelD, dutyCycleD);
};