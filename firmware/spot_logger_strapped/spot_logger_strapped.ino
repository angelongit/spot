// Spot data logger: streams IMU data as CSV at a fixed 100 Hz
// Format: t_ms,ax,ay,az,gx,gy,gz   (accel in g, gyro in deg/s)

#include "LSM6DS3.h"
#include "Wire.h"

LSM6DS3 imu(I2C_MODE, 0x6A);

const unsigned long SAMPLE_US = 10000;  // 100 Hz
unsigned long nextSample = 0;
unsigned long t0 = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);  // wait for USB serial so no data is lost at start

  if (imu.begin() != 0) {
    Serial.println("# IMU error");
    while (1);
  }
  Serial.println("t_ms,ax,ay,az,gx,gy,gz");
  t0 = millis();
  nextSample = micros();
}

void loop() {
  if ((long)(micros() - nextSample) < 0) return;
  nextSample += SAMPLE_US;

  Serial.print(millis() - t0); Serial.print(',');
  Serial.print(imu.readFloatAccelX(), 3); Serial.print(',');
  Serial.print(imu.readFloatAccelY(), 3); Serial.print(',');
  Serial.print(imu.readFloatAccelZ(), 3); Serial.print(',');
  Serial.print(imu.readFloatGyroX(), 2);  Serial.print(',');
  Serial.print(imu.readFloatGyroY(), 2);  Serial.print(',');
  Serial.println(imu.readFloatGyroZ(), 2);
}
