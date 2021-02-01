#include "Adafruit_Sensor_Calibration.h"

// select either EEPROM or SPI FLASH storage:
#ifdef ADAFRUIT_SENSOR_CALIBRATION_USE_EEPROM
  Adafruit_Sensor_Calibration_EEPROM cal;
#else
  Adafruit_Sensor_Calibration_SDFat cal;
#endif

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  delay(100);
  Serial.println("Calibration filesys test");
  if (!cal.begin()) {
    Serial.println("Failed to initialize calibration helper");
    while (1) yield();
  }
  Serial.print("Has EEPROM: "); Serial.println(cal.hasEEPROM());
  Serial.print("Has FLASH: "); Serial.println(cal.hasFLASH());

  if (! cal.loadCalibration()) {
    Serial.println("No calibration loaded/found... will start with defaults");
  } else {
    Serial.println("Loaded existing calibration");
  }

  // in uTesla
  cal.mag_hardiron[0] = 21.20;
  cal.mag_hardiron[1] = 17.25;
  cal.mag_hardiron[2] = -45.47;

  // in uTesla
  cal.mag_softiron[0] = 1.034;
  cal.mag_softiron[1] = -0.016;
  cal.mag_softiron[2] = -0.004;  
  cal.mag_softiron[3] = -0.016;
  cal.mag_softiron[4] = 0.992;
  cal.mag_softiron[5] = -0.004;  
  cal.mag_softiron[6] = -0.004;
  cal.mag_softiron[7] = -0.004;
  cal.mag_softiron[8] = 0.976;  

  // in Radians/s
  cal.gyro_zerorate[0] = 0.000;
  cal.gyro_zerorate[1] = 0.000;
  cal.gyro_zerorate[2] = 0.000;

  if (! cal.saveCalibration()) {
    Serial.println("**WARNING** Couldn't save calibration");
  } else {
    Serial.println("Wrote calibration");    
  }

  cal.printSavedCalibration();
}

void loop() {

}
