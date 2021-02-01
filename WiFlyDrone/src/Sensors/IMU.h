#include "MPU9250.h"

#define SENSORS_RADS_TO_DPS                                                    \
  (57.29577793F) /**< Rad/s to degrees/s  multiplier */

// Alternative I2C Definition
#define SDA2 13// 14
#define SCL2 14// 2
TwoWire I2Ctwo = TwoWire(0);

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(I2Ctwo,0x68);
int status;

// Globabl Variable to Store Measured IMU Data
double * IMU_data;

// Setup IMU
void setupIMU(){
    Serial.println("Setting up IMU...");

    // start communication with IMU
    // Setup Alternative I2C
    I2Ctwo.begin(SDA2,SCL2, 400000);

    // Start IMU
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

    // setting the accelerometer full scale range to +/-8G 
    IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
    // setting the gyroscope full scale range to +/-500 deg/s
    IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
    // setting DLPF bandwidth to 20 Hz
    IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
    // setting SRD to 19 for a 50 Hz update rate
    IMU.setSrd(19);
}

// Convert Acceleration to Roll Pitch Yaw
double* getRollPitchAccel(int16_t x, int16_t y, int16_t z, double *rp_tmp){
   double X = float(x);
   double Y = float(y);
   double Z = float(z);
   double roll_a = atan2(Y, Z);
   //Serial.println(roll_a);
   double pitch_a = atan2((-X), sqrt(Y*Y +Z*Z));
   //Serial.println(pitch_a);
   rp_tmp[0] = roll_a;
   rp_tmp[1] = pitch_a;
   return rp_tmp;
}

double * getIMU_vals(){
    // Read IMU Data
    IMU.readSensor();

   // Get the Roll and Pitch
   double rp_tmp[5];
   double * rollPitch_accel = getRollPitchAccel(IMU.getAccelX_mss(), IMU.getAccelY_mss(), IMU.getAccelZ_mss(), rp_tmp);
   double roll = rollPitch_accel[0];
   double pitch = rollPitch_accel[1];

   // Get the Yaw from Magnetometer
   double Yh = (IMU.getMagY_uT() * cos(roll)) - (IMU.getMagZ_uT() * sin(roll));
   double Xh = (IMU.getMagX_uT() * cos(pitch))+(IMU.getMagY_uT() * sin(roll)*sin(pitch)) + (IMU.getMagZ_uT() * cos(roll) * sin(pitch));
   double yaw = atan2(Yh, Xh);

   // --- Create Container for Data ---
   double static IMU_data[10];

   IMU_data[0] = roll;//rollPitch_accel[0];
   IMU_data[1] = pitch;//rollPitch_accel[1];
   IMU_data[2] = yaw;
  
   return IMU_data;
}

void printIMU(){
    // Read IMU Data
    IMU.readSensor();

    // Display IMU Data
    /*
    Serial.print(IMU.getAccelX_mss(),6);
    Serial.print("\t");
    Serial.print(IMU.getAccelY_mss(),6);
    Serial.print("\t");
    Serial.print(IMU.getAccelZ_mss(),6);
    Serial.print("\t");
    Serial.print(IMU.getGyroX_rads(),6);
    Serial.print("\t");
    Serial.print(IMU.getGyroY_rads(),6);
    Serial.print("\t");
    Serial.print(IMU.getGyroZ_rads(),6);
    Serial.print("\t");
    Serial.print(IMU.getMagX_uT(),6);
    Serial.print("\t");
    Serial.print(IMU.getMagY_uT(),6);
    Serial.print("\t");
    Serial.print(IMU.getMagZ_uT(),6);
    Serial.print("\t");
    Serial.println(IMU.getTemperature_C(),6);*/


    // 'Raw' values to match expectation of MotionCal
    Serial.print("Raw:");
    Serial.print(int(IMU.getAccelX_mss()*8192/9.8)); Serial.print(",");
    Serial.print(int(IMU.getAccelY_mss()*8192/9.8)); Serial.print(",");
    Serial.print(int(IMU.getAccelZ_mss()*8192/9.8)); Serial.print(",");
    Serial.print(int(IMU.getGyroX_rads()*SENSORS_RADS_TO_DPS*16)); Serial.print(",");
    Serial.print(int(IMU.getGyroY_rads()*SENSORS_RADS_TO_DPS*16)); Serial.print(",");
    Serial.print(int(IMU.getGyroZ_rads()*SENSORS_RADS_TO_DPS*16)); Serial.print(",");
    Serial.print(int(IMU.getMagX_uT()*10)); Serial.print(",");
    Serial.print(int(IMU.getMagY_uT()*10)); Serial.print(",");
    Serial.print(int(IMU.getMagZ_uT()*10)); Serial.println("");

    // unified data
    Serial.print("Uni:");
    Serial.print(IMU.getAccelX_mss()); Serial.print(",");
    Serial.print(IMU.getAccelY_mss()); Serial.print(",");
    Serial.print(IMU.getAccelZ_mss()); Serial.print(",");
    Serial.print(IMU.getGyroX_rads(), 4); Serial.print(",");
    Serial.print(IMU.getGyroY_rads(), 4); Serial.print(",");
    Serial.print(IMU.getGyroZ_rads(), 4); Serial.print(",");
    Serial.print(IMU.getMagX_uT()); Serial.print(",");
    Serial.print(IMU.getMagY_uT()); Serial.print(",");
    Serial.print(IMU.getMagZ_uT()); Serial.println("");
    }