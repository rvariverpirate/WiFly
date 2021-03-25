/* MPU9250 Basic Example Code
 by: Kris Winer
 date: April 1, 2014
 license: Beerware - Use this code however you'd like. If you
 find it useful you can buy me a beer some time.
 Modified by Brent Wilkins July 19, 2016
 Modified by River Rat February 3, 2021

 Demonstrate basic MPU-9250 functionality including parameterizing the register
 addresses, initializing the sensor, getting properly scaled accelerometer,
 gyroscope, and magnetometer data out. Added display functions to allow display
 to on breadboard monitor. Addition of 9 DoF sensor fusion using open source
 Madgwick and Mahony filter algorithms.

 RVA River Pirate:
 Modified to run on ESP32CAM in alternate I2C setup 
 and tweaked to be compatible with PlatformIO.


 SDA and SCL should have external pull-up resistors (to 3.3V).
 10k resistors are on the EMSENSR-9250 breakout board.

 Hardware setup:
 MPU9250 Breakout --------- Arduino
 VDD ---------------------- 3.3V
 VDDI --------------------- 3.3V
 SDA ----------------------- A4
 SCL ----------------------- A5
 GND ---------------------- GND
 */

#include "quaternionFilters.h"
#include "MPU9250.h"

#define SerialDebug false// Set to true to get Serial output for debugging

#define RADS_TO_DEG (57.29577793F) // Radians to Degrees  multiplier
#define DEG_TO_RAD 1.0/(57.29577793F) // Degrees to Radians multiplier



// Pin definitions
int myLed  = 33;  // Set up pin 13 led for toggling

// Alternative I2C Definition
#define SDA2 13// Bread Board: 13// 14
#define SCL2 15// Bread Board: 14// 2
TwoWire I2Ctwo = TwoWire(0);
#define I2Cclock 400000
#define MPU9250_ADDRESS MPU9250_ADDRESS_AD0   // Use either this line or the next to select which I2C address your device is using
//#define MPU9250_ADDRESS MPU9250_ADDRESS_AD1

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 AHRS(MPU9250_ADDRESS, I2Ctwo, I2Cclock);

void setupAHRS()
{
  I2Ctwo.begin(SDA2,SCL2, 400000);
  // TWBR = 12;  // 400 kbit/sec I2C speed

  while(!Serial){};

  pinMode(myLed, OUTPUT);
  digitalWrite(myLed, HIGH);


  // Read the WHO_AM_I register, this is a good test of communication
  byte c = AHRS.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
  Serial.print(F("MPU9250 I AM 0x"));
  Serial.print(c, HEX);
  Serial.print(F(" I should be 0x"));
  Serial.println(0x71, HEX);

  if (c == 0x73) // WHO_AM_I should always be 0x71: Why is mine always 0x73?
  {
    Serial.println(F("MPU9250 is online..."));

    // Start by performing self test and reporting values
    AHRS.MPU9250SelfTest(AHRS.selfTest);
    Serial.print(F("x-axis self test: acceleration trim within : "));
    Serial.print(AHRS.selfTest[0],1); Serial.println("% of factory value");
    Serial.print(F("y-axis self test: acceleration trim within : "));
    Serial.print(AHRS.selfTest[1],1); Serial.println("% of factory value");
    Serial.print(F("z-axis self test: acceleration trim within : "));
    Serial.print(AHRS.selfTest[2],1); Serial.println("% of factory value");
    Serial.print(F("x-axis self test: gyration trim within : "));
    Serial.print(AHRS.selfTest[3],1); Serial.println("% of factory value");
    Serial.print(F("y-axis self test: gyration trim within : "));
    Serial.print(AHRS.selfTest[4],1); Serial.println("% of factory value");
    Serial.print(F("z-axis self test: gyration trim within : "));
    Serial.print(AHRS.selfTest[5],1); Serial.println("% of factory value");


    // Calibrate gyro and accelerometers, load biases in bias registers
    Serial.println("About to Calibrate Accel and Gyro, do not move device for a moment.");
    delay(3000);
    Serial.println("Beginning Accel Gro Cal");
    AHRS.calibrateMPU9250(AHRS.gyroBias, AHRS.accelBias);
    Serial.println("Accel Gryo Cal Done!");

    AHRS.initMPU9250();
    // Initialize device for active mode read of acclerometer, gyroscope, and
    // temperature
    Serial.println("MPU9250 initialized for active data mode....");

    // Read the WHO_AM_I register of the magnetometer, this is a good test of
    // communication
    byte d = AHRS.readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);
    Serial.print("AK8963 ");
    Serial.print("I AM 0x");
    Serial.print(d, HEX);
    Serial.print(" I should be 0x");
    Serial.println(0x48, HEX);

    if (d != 0x48)
    {
      // Communication failed, stop here
      Serial.println(F("Communication failed, abort!"));
      Serial.flush();
      abort();
    }

    // Get magnetometer calibration from AK8963 ROM
    AHRS.initAK8963(AHRS.factoryMagCalibration);
    // Initialize device for active mode read of magnetometer
    Serial.println("AK8963 initialized for active data mode....");

    if (SerialDebug)
    {
      //  Serial.println("Calibration values: ");
      Serial.print("X-Axis factory sensitivity adjustment value ");
      Serial.println(AHRS.factoryMagCalibration[0], 2);
      Serial.print("Y-Axis factory sensitivity adjustment value ");
      Serial.println(AHRS.factoryMagCalibration[1], 2);
      Serial.print("Z-Axis factory sensitivity adjustment value ");
      Serial.println(AHRS.factoryMagCalibration[2], 2);
    }

    // Get sensor resolutions, only need to do this once
    AHRS.getAres();
    AHRS.getGres();
    AHRS.getMres();

    // The next call delays for 4 seconds, and then records about 15 seconds of
    // data to calculate bias and scale.

    // Calibrate Magnetometer
    Serial.println("Beginning Mag Calibration in ");
    Serial.print("5 ");
    delay(1000);
    Serial.print("4 ");
    delay(1000);
    Serial.print("3 ");
    delay(1000);
    Serial.print("2 ");
    delay(1000);
    Serial.print("1 ");
    delay(1000);
    Serial.println("Mag val beginning, move in Figure 8 pattern");
    AHRS.magCalMPU9250(AHRS.magBias, AHRS.magScale);
    Serial.println("Mag calibration done!");
    Serial.println("AK8963 mag biases (mG)");
    Serial.println(AHRS.magBias[0]);
    Serial.println(AHRS.magBias[1]);
    Serial.println(AHRS.magBias[2]);

    Serial.println("AK8963 mag scale (mG)");
    Serial.println(AHRS.magScale[0]);
    Serial.println(AHRS.magScale[1]);
    Serial.println(AHRS.magScale[2]);
    //    delay(2000); // Add delay to see results before serial spew of data

    if(SerialDebug)
    {
      Serial.println("Magnetometer:");
      Serial.print("X-Axis sensitivity adjustment value ");
      Serial.println(AHRS.factoryMagCalibration[0], 2);
      Serial.print("Y-Axis sensitivity adjustment value ");
      Serial.println(AHRS.factoryMagCalibration[1], 2);
      Serial.print("Z-Axis sensitivity adjustment value ");
      Serial.println(AHRS.factoryMagCalibration[2], 2);
    }

  } // if (c == 0x71)
  else
  {
    Serial.print("Could not connect to MPU9250: 0x");
    Serial.println(c, HEX);

    // Communication failed, stop here
    Serial.println(F("Communication failed, abort!"));
    Serial.flush();
    abort();
  }
  delay(5000);
}

void updateAHRS()
{
    // If intPin goes high, all data registers have new data
    // On interrupt, check if data ready interrupt
    if (AHRS.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
    {
        AHRS.readAccelData(AHRS.accelCount);  // Read the x/y/z adc values

        // Now we'll calculate the accleration value into actual g's
        // This depends on scale being set
        AHRS.ax = (float)AHRS.accelCount[0] * AHRS.aRes; // - AHRS.accelBias[0];
        AHRS.ay = (float)AHRS.accelCount[1] * AHRS.aRes; // - AHRS.accelBias[1];
        AHRS.az = (float)AHRS.accelCount[2] * AHRS.aRes; // - AHRS.accelBias[2];

        AHRS.readGyroData(AHRS.gyroCount);  // Read the x/y/z adc values

        // Calculate the gyro value into actual degrees per second
        // This depends on scale being set
        AHRS.gx = (float)AHRS.gyroCount[0] * AHRS.gRes;
        AHRS.gy = (float)AHRS.gyroCount[1] * AHRS.gRes;
        AHRS.gz = (float)AHRS.gyroCount[2] * AHRS.gRes;

        AHRS.readMagData(AHRS.magCount);  // Read the x/y/z adc values

        // Calculate the magnetometer values in milliGauss
        // Include factory calibration per data sheet and user environmental
        // corrections
        // Get actual magnetometer value, this depends on scale being set
        AHRS.mx = (float)AHRS.magCount[0] * AHRS.mRes
                * AHRS.factoryMagCalibration[0] - AHRS.magBias[0];
        AHRS.my = (float)AHRS.magCount[1] * AHRS.mRes
                * AHRS.factoryMagCalibration[1] - AHRS.magBias[1];
        AHRS.mz = (float)AHRS.magCount[2] * AHRS.mRes
                * AHRS.factoryMagCalibration[2] - AHRS.magBias[2];
    } // if (readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)

    // Must be called before updating quaternions!
    AHRS.updateTime();

    // Sensors x (y)-axis of the accelerometer is aligned with the y (x)-axis of
    // the magnetometer; the magnetometer z-axis (+ down) is opposite to z-axis
    // (+ up) of accelerometer and gyro! We have to make some allowance for this
    // orientationmismatch in feeding the output to the quaternion filter. For the
    // MPU-9250, we have chosen a magnetic rotation that keeps the sensor forward
    // along the x-axis just like in the LSM9DS0 sensor. This rotation can be
    // modified to allow any convenient orientation convention. This is ok by
    // aircraft orientation standards! Pass gyro rate as rad/s
    
    /*MahonyQuaternionUpdate(AHRS.ax, AHRS.ay, AHRS.az, AHRS.gx * DEG_TO_RAD,
                            AHRS.gy * DEG_TO_RAD, AHRS.gz * DEG_TO_RAD, AHRS.my,
                            AHRS.mx, AHRS.mz, AHRS.deltat);*/ //Running at ~4kHz
  
    MadgwickQuaternionUpdate(AHRS.ax, AHRS.ay, AHRS.az, AHRS.gx * DEG_TO_RAD,
                         AHRS.gy * DEG_TO_RAD, AHRS.gz * DEG_TO_RAD, AHRS.my,
                         AHRS.mx, AHRS.mz, AHRS.deltat);

    // Serial print and/or display at 0.5 s rate independent of data rates
    AHRS.delt_t = millis() - AHRS.count;

    if(SerialDebug)
    {
        Serial.print("ax = ");  Serial.print((int)1000 * AHRS.ax);
        Serial.print(" ay = "); Serial.print((int)1000 * AHRS.ay);
        Serial.print(" az = "); Serial.print((int)1000 * AHRS.az);
        Serial.println(" mg");

        Serial.print("gx = ");  Serial.print(AHRS.gx, 2);
        Serial.print(" gy = "); Serial.print(AHRS.gy, 2);
        Serial.print(" gz = "); Serial.print(AHRS.gz, 2);
        Serial.println(" deg/s");

        Serial.print("mx = ");  Serial.print((int)AHRS.mx);
        Serial.print(" my = "); Serial.print((int)AHRS.my);
        Serial.print(" mz = "); Serial.print((int)AHRS.mz);
        Serial.println(" mG");

        Serial.print("q0 = ");  Serial.print(*getQ());
        Serial.print(" qx = "); Serial.print(*(getQ() + 1));
        Serial.print(" qy = "); Serial.print(*(getQ() + 2));
        Serial.print(" qz = "); Serial.println(*(getQ() + 3));
    }

    // Define output variables from updated quaternion---these are Tait-Bryan
    // angles, commonly used in aircraft orientation. In this coordinate system,
    // the positive z-axis is down toward Earth. Yaw is the angle between Sensor
    // x-axis and Earth magnetic North (or true North if corrected for local
    // declination, looking down on the sensor positive yaw is counterclockwise.
    // Pitch is angle between sensor x-axis and Earth ground plane, toward the
    // Earth is positive, up toward the sky is negative. Roll is angle between
    // sensor y-axis and Earth ground plane, y-axis up is positive roll. These
    // arise from the definition of the homogeneous rotation matrix constructed
    // from quaternions. Tait-Bryan angles as well as Euler angles are
    // non-commutative; that is, the get the correct orientation the rotations
    // must be applied in the correct order which for this configuration is yaw,
    // pitch, and then roll.
    // For more see
    // http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    // which has additional links.
    AHRS.yaw   = atan2(2.0f * (*(getQ()+1) * *(getQ()+2) + *getQ()
                * *(getQ()+3)), *getQ() * *getQ() + *(getQ()+1)
                * *(getQ()+1) - *(getQ()+2) * *(getQ()+2) - *(getQ()+3)
                * *(getQ()+3));
    AHRS.pitch = -asin(2.0f * (*(getQ()+1) * *(getQ()+3) - *getQ()
                * *(getQ()+2)));
    AHRS.roll  = atan2(2.0f * (*getQ() * *(getQ()+1) + *(getQ()+2)
                * *(getQ()+3)), *getQ() * *getQ() - *(getQ()+1)
                * *(getQ()+1) - *(getQ()+2) * *(getQ()+2) + *(getQ()+3)
                * *(getQ()+3));
    // AHRS.pitch *= RAD_TO_DEG;
    // AHRS.yaw   *= RAD_TO_DEG;

    // Declination of SparkFun Electronics (40°05'26.6"N 105°11'05.9"W) is
    // 	8° 30' E  ± 0° 21' (or 8.5°) on 2016-07-19
    // - http://www.ngdc.noaa.gov/geomag-web/#declination
    // AHRS.yaw  -= 8.5;
    // AHRS.roll *= RAD_TO_DEG;

    if(SerialDebug)
    {
        Serial.print("Roll, Pitch, Yaw: ");
        Serial.print(AHRS.roll, 2);
        Serial.print(", ");
        Serial.print(AHRS.pitch, 2);
        Serial.print(", ");
        Serial.println(AHRS.yaw, 2);

        Serial.print("rate = ");
        Serial.print((float)AHRS.sumCount / AHRS.sum, 2);
        Serial.println(" Hz");
    }

    // With these settings the filter is updating at a ~145 Hz rate using the
    // Madgwick scheme and >200 Hz using the Mahony scheme even though the
    // display refreshes at only 2 Hz. The filter update rate is determined
    // mostly by the mathematical steps in the respective algorithms, the
    // processor speed (8 MHz for the 3.3V Pro Mini), and the magnetometer ODR:
    // an ODR of 10 Hz for the magnetometer produce the above rates, maximum
    // magnetometer ODR of 100 Hz produces filter update rates of 36 - 145 and
    // ~38 Hz for the Madgwick and Mahony schemes, respectively. This is
    // presumably because the magnetometer read takes longer than the gyro or
    // accelerometer reads. This filter update rate should be fast enough to
    // maintain accurate platform orientation for stabilization control of a
    // fast-moving robot or quadcopter. Compare to the update rate of 200 Hz
    // produced by the on-board Digital Motion Processor of Invensense's MPU6050
    // 6 DoF and MPU9150 9DoF sensors. The 3.3 V 8 MHz Pro Mini is doing pretty
    // well!

    AHRS.count = millis();
    AHRS.sumCount = 0;
    AHRS.sum = 0;
}