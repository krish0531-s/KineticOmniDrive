#include "USBHost_t36.h"

// --- USB Host objects ---
USBHost mysub;
USBHub hub1(mysub);                // Optional USB hub
JoystickController joystick1(mysub); // For wired joystick
//BluetoothController bluet(mysub);    // Generic Bluetooth controller
BluetoothController bluet(mysub, true, "0000"); 
void setup() {
  Serial1.begin(115200);
  while (!Serial);

  Serial.println("Starting USB Host...");
  mysub.begin();  // Initialize USB host
  Serial.println("USB Host started.");
}

void loop() {
  mysub.Task();  // Keep USB Host stack running

  // --- Read wired joystick axes ---
  if (joystick1.available()) {
    int lx = joystick1.getAxis(0);
    int ly = joystick1.getAxis(1);
    int rx = joystick1.getAxis(2);
    int ry = joystick1.getAxis(3);

    Serial.print("Joystick Lx:"); Serial.print(lx);
    Serial.print(" Ly:"); Serial.print(ly);
    Serial.print(" | Rx:"); Serial.print(rx);
    Serial.print(" Ry:"); Serial.println(ry);
  }

  
  

  delay(100); // small delay to avoid spamming Serial
}
