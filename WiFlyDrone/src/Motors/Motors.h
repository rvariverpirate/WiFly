
#ifndef Motors_h
#define Motors_h
#include "Arduino.h"
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

// Clockwise from top-right
#define MotorA 12 // Right Front Motor
#define ChannelA 0 // PWM Channel (0-15)
#define MotorB 4 // Right Back Motor
#define ChannelB 1 // PWM Channel
#define MotorC 2 // Left Front Motor
#define ChannelC 2 // PWM Channel
#define MotorD 14 // Left Back Motor
#define ChannelD 3 // PWM Channel
#define PWM_RESOLUTION 8 // 8-bit resolution
#define PWM_FREQ 5000// Keep above motor constant to only DC is present

class Motors
{
    public:
        // Constructor
        Motors();

        // Define motors as outputs and setup for PWM
        void setupMotors();

        // Update all motors PWM
        void updateMotors(double dutyCycleA, double dutyCycleB, double dutyCycleC, double dutyCycleD);
};
#endif