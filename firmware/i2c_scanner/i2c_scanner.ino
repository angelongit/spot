// Rep Tracker - Step 2: I2C scanner
// Checks every possible I2C address and reports which ones answer.
// Expected result with the GY-521: a device at 0x68.

#include <Wire.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) { }        // wait for the Serial Monitor (harmless on the Mega)
  Wire.begin();              // start the I2C bus (Mega pins 20 = SDA, 21 = SCL)
  Serial.println("I2C scanner starting...");
}

void loop() {
  int found = 0;

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);       // "is anyone at this address?"
    byte result = Wire.endTransmission();  // 0 means a device answered

    if (result == 0) {
      Serial.print("Device found at 0x");
      if (address < 16) Serial.print('0');
      Serial.println(address, HEX);
      found++;
    }
  }

  if (found == 0) {
    Serial.println("No devices found - check SDA/SCL, VCC and GND.");
  } else {
    Serial.print("Scan done, ");
    Serial.print(found);
    Serial.println(" device(s) found.");
  }

  Serial.println();
  delay(3000);               // scan again every 3 seconds
}
