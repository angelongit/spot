// Rep Tracker - Step 3 (no-library version): stream MPU6050 data from the Mega
// Talks to the sensor directly through its registers, so it also works with
// clone / substitute chips that the Adafruit library rejects.
//
// Wiring: VCC->5V, GND->GND, SDA->20, SCL->21
//
// Two output modes:
//   PLOTTER_MODE = true   -> labeled values for the Arduino Serial Plotter
//   PLOTTER_MODE = false  -> CSV for log_set.py (same format as the XIAO sketch):
//                            time_ms,ax,ay,az,gx,gy,gz
// Acceleration is in g, rotation is in degrees per second.

#include <Wire.h>

const bool PLOTTER_MODE = false;               // change to false before logging sets

const uint8_t MPU_ADDR = 0x68;                // address the I2C scanner found

// Register addresses (from the MPU6050 register map)
const uint8_t REG_CONFIG       = 0x1A;        // built-in low-pass filter
const uint8_t REG_GYRO_CONFIG  = 0x1B;        // gyro range
const uint8_t REG_ACCEL_CONFIG = 0x1C;        // accel range
const uint8_t REG_ACCEL_XOUT_H = 0x3B;        // first of 14 data bytes
const uint8_t REG_PWR_MGMT_1   = 0x6B;        // power / sleep control
const uint8_t REG_WHO_AM_I     = 0x75;        // chip ID

// Scale factors for the ranges chosen below
const float ACCEL_LSB_PER_G   = 8192.0;       // +/- 4 g range
const float GYRO_LSB_PER_DPS  = 65.5;         // +/- 500 deg/s range

const unsigned long SAMPLE_INTERVAL_MS = 10;  // 10 ms = 100 samples per second
unsigned long lastSample = 0;

// Write one byte to a sensor register
void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

// Read one byte from a sensor register
uint8_t readRegister(uint8_t reg) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);                // keep the bus for the read
  Wire.requestFrom(MPU_ADDR, (uint8_t)1);
  return Wire.available() ? Wire.read() : 0xFF;
}

void setup() {
  Serial.begin(115200);
    delay(3000);
  Wire.begin();

  // The chip starts asleep - wake it up and use the gyro's clock (more stable)
  writeRegister(REG_PWR_MGMT_1, 0x01);
  writeRegister(0x1D, 0x03);  // MPU-6500 only: accel low-pass filter ~41 Hz
  delay(100);

  writeRegister(REG_CONFIG, 0x03);            // low-pass filter ~44 Hz
  writeRegister(REG_ACCEL_CONFIG, 0x08);      // +/- 4 g
  writeRegister(REG_GYRO_CONFIG, 0x08);       // +/- 500 deg/s

  if (PLOTTER_MODE) {
    // Shown in the Serial Monitor only; useful to know which chip you have
    Serial.print("WHO_AM_I = 0x");
    Serial.println(readRegister(REG_WHO_AM_I), HEX);
  } else {
    Serial.println("time_ms,ax,ay,az,gx,gy,gz");  // CSV header
  }
}

// Combine a high and low byte into one signed 16-bit number
int16_t toInt16(uint8_t high, uint8_t low) {
  return (int16_t)((high << 8) | low);
}

void loop() {
  unsigned long now = millis();
  if (now - lastSample < SAMPLE_INTERVAL_MS) return;  // keep a steady 100 Hz
  lastSample = now;

  // Read all 14 data bytes in one go: accel X/Y/Z, temperature, gyro X/Y/Z
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(REG_ACCEL_XOUT_H);
  Wire.endTransmission(false);
  if (Wire.requestFrom(MPU_ADDR, (uint8_t)14) != 14) return;  // skip a bad read

  uint8_t b[14];
  for (int i = 0; i < 14; i++) b[i] = Wire.read();

  float ax = toInt16(b[0],  b[1])  / ACCEL_LSB_PER_G;
  float ay = toInt16(b[2],  b[3])  / ACCEL_LSB_PER_G;
  float az = toInt16(b[4],  b[5])  / ACCEL_LSB_PER_G;
  // b[6], b[7] are temperature - not needed
  float gx = toInt16(b[8],  b[9])  / GYRO_LSB_PER_DPS;
  float gy = toInt16(b[10], b[11]) / GYRO_LSB_PER_DPS;
  float gz = toInt16(b[12], b[13]) / GYRO_LSB_PER_DPS;

  if (PLOTTER_MODE) {
    // Gyro divided by 100 so it fits on the same scale as accel
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
