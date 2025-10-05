#include <PS4BT.h>
#include <usbhub.h>

USB Usb;
BTD Btd(&Usb);
PS4BT PS4(&Btd);

void setup() {
  Serial.begin(115200);
  Usb.Init();
  Serial.println("Waiting for PS4 controller...");
}

void loop() {
  Usb.Task();

  if (PS4.connected()) {
    int lx = PS4.getAnalogHat(LeftHatX);
    int ly = PS4.getAnalogHat(LeftHatY);
    int rx = PS4.getAnalogHat(RightHatX);
    int ry = PS4.getAnalogHat(RightHatY);

    Serial.print(lx); Serial.print(" ");
    Serial.print(ly); Serial.print(" ");
    Serial.print(rx); Serial.print(" ");
    Serial.println(ry);
  }
}
