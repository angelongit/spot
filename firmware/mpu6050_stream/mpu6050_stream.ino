// Rep Tracker - Step 3: stream MPU6050 data from the Arduino Mega
// Wiring: VCC->5V, GND->GND, SDA->20, SCL->21
// Library: "Adafruit MPU6050" (installs Adafruit Unified Sensor + BusIO too)
//
// Two output modes:
//   PLOTTER_MODE = true   -> labeled values for the Arduino Serial Plotter
//   PLOTTER_MODE = false  -> CSV for log_set.py (same format as the XIAO sketch):
//                            time_ms,ax,ay,az,gx,gy,gz
// Acceleration is in g, rotation is in degrees per second.

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

const bool PLOTTER_MODE = true;               // change to false before logging sets

const unsigned long SAMPLE_INTERVAL_MS = 10;  // 10 ms = 100 samples per second
const float MS2_TO_G   = 1.0 / 9.80665;       // library gives m/s^2, we want g
const float RAD_TO_DPS = 57.29578;            // library gives rad/s, we want deg/s

Adafruit_MPU6050 mpu;
unsigned long lastSample = 0;

void setup() {
  Serial.begin(115200);

  if (!mpu.begin()) {                         // looks for the sensor at 0x68
    Serial.println("MPU6050 not found - check wiring");
    while (true) { }
  }

  // Ranges: wide enough that fast reps don't max out the sensor
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);     // +/- 4 g
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);          // +/- 500 deg/s
  mpu.setFilterBandwidth(MPU6050_BAND_44_HZ);       // light built-in smoothing

  if (!PLOTTER_MODE) {
    Serial.println("time_ms,ax,ay,az,gx,gy,gz");    // CSV header
  }
}

void loop() {
  unsigned long now = millis();
  if (now - lastSample < SAMPLE_INTERVAL_MS) return;  // keep a steady 100 Hz
  lastSample = now;

  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  float ax = accel.acceleration.x * MS2_TO_G;
  float ay = accel.acceleration.y * MS2_TO_G;
  float az = accel.acceleration.z * MS2_TO_G;
  float gx = gyro.gyro.x * RAD_TO_DPS;
  float gy = gyro.gyro.y * RAD_TO_DPS;
  float gz = gyro.gyro.z * RAD_TO_DPS;

  if (PLOTTER_MODE) {
    // "label:value" pairs so the Serial Plotter names each line.
    // Gyro is divided by 100 so it fits on the same scale as accel.
    Serial.print("ax:");      Serial.print(ax, 3);
    Serial.print(",ay:");     Serial.print(ay, 3);
    Serial.print(",az:");     Serial.print(az, 3);
    Serial.print(",gx/100:"); Serial.print(gx / 100.0, 3);
    Serial.print(",gy/100:"); Serial.print(gy / 100.0, 3);
    Serial.print(",gz/100:"); Serial.println(gz / 100.0, 3);
  } else {
    Serial.print(now);     Serial.print(',');
    Serial.print(ax, 3);   Serial.print(',');
    Serial.print(ay, 3);   Serial.print(',');
    Serial.print(az, 3);   Serial.print(',');
    Serial.print(gx, 2);   Serial.print(',');
    Serial.print(gy, 2);   Serial.print(',');
    Serial.println(gz, 2);
  }
}
