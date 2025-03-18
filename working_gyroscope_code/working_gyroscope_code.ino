#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM6DS33.h>

// Create an instance of the LSM6DS3 class
Adafruit_LSM6DS33 lsm6ds33;

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);  // wait for serial port to open

  Serial.println("Adafruit LSM6DS33 test!");

  // Try to initialize the sensor with the detected address
  if (!lsm6ds33.begin_I2C(0x6B)) { // Use the detected address here
    Serial.println("Failed to find LSM6DS33 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("LSM6DS33 Found!");
}

void loop() {
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;

  // Get new data from the sensor
  lsm6ds33.getEvent(&accel, &gyro, &temp);

  // Print accelerometer data
  Serial.print("Accel X: "); Serial.print(accel.acceleration.x); Serial.print(" m/s^2");
  Serial.print("\tY: "); Serial.print(accel.acceleration.y); Serial.print(" m/s^2");
  Serial.print("\tZ: "); Serial.print(accel.acceleration.z); Serial.println(" m/s^2");

  // Print gyroscope data
  Serial.print("Gyro X: "); Serial.print(gyro.gyro.x); Serial.print(" rad/s");
  Serial.print("\tY: "); Serial.print(gyro.gyro.y); Serial.print(" rad/s");
  Serial.print("\tZ: "); Serial.print(gyro.gyro.z); Serial.println(" rad/s");

  // Print temperature data
  Serial.print("Temp: "); Serial.print(temp.temperature); Serial.println(" C");

  delay(1000);
}
