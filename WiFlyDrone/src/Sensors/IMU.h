#include "MPU9250.h"

// Alternative I2C Definition
#define SDA2 14
#define SCL2 2
TwoWire I2Ctwo = TwoWire(0);

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(I2Ctwo,0x68);
int status;

// Setup IMU
void setupIMU(){
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println();
    Serial.println("Setting up IMU...");

    // start communication with IMU
    // Setup Alternative I2C
    I2Ctwo.begin(SDA2,SCL2, 400000);

    // IMU Begin Breaks things
    status = IMU.begin();
    if (status < 0) {
        Serial.println("IMU initialization unsuccessful");
        Serial.println("Check IMU wiring or try cycling power");
        Serial.print("Status: ");
        Serial.println(status);
    }
    else{
        Serial.println("IMU Checks out!");
    }
}