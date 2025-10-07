#include "USBHost_t36.h"

// USB Host objects 
USBHost mysub;
USBHub hub1(mysub);                
JoystickController joystick1(mysub); 
BluetoothController bluet(mysub, true, "0000"); 

// Robot geometry
const float r = 0.03; // wheel radius (meters)
const float L = 0.1;  // distance from center to wheel
float V1, V2, V3;     // wheel velocities

const int pwmPin1 = 3;
const int dirPin1 = 4;

const int pwmPin2 = 5;
const int dirPin2 = 6;

const int pwmPin3 = 9;
const int dirPin3 = 10;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Starting USB Host...");
  mysub.begin();
  Serial.println("USB Host started.");


  pinMode(pwmPin1, OUTPUT); pinMode(dirPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT); pinMode(dirPin2, OUTPUT);
  pinMode(pwmPin3, OUTPUT); pinMode(dirPin3, OUTPUT);
}

void driveMotor(float omegaDir, int pwmPin, int dirPin, float pwmValue){
  digitalWrite(dirPin, omegaDir>=0 ? HIGH : LOW);
  analogWrite(pwmPin, pwmValue);
}



void loop() {
  mysub.Task();  // keep USB Host running

  int lx=0, ly=0, rx=0;

  // Read wired joystick axes 
  if (joystick1.available()) {
    lx = joystick1.getAxis(0);  // Left stick X
    ly = joystick1.getAxis(1);  // Left stick Y
    rx = joystick1.getAxis(2);  // Right stick X (rotation)

    Serial.print("Joystick Lx:"); Serial.print(lx);
    Serial.print(" Ly:"); Serial.print(ly);
    Serial.print(" | Rx:"); Serial.println(rx);
  }

  //  Map joystick to robot velocities (-1 to 1) 
  float Vx = (lx - 512)/512.0;  
  float Vy = (ly - 512)/512.0;
  float omega = (rx - 512)/512.0;

  //Deadzone to ignore values near centre
  float deadzone = 0.1;
  if(abs(Vx) < deadzone){
    Vx = 0;
  }
  if(abs(Vy) < deadzone){
    Vy = 0;
  }
  if (abs(omega) < deadzone){
    omega = 0;
  }


  // Inverse kinematics for 3-wheeled omni
  V1 = -sin(0) * Vx + cos(0) * Vy + L * omega;
  V2 = -sin(2.0*PI/3) * Vx + cos(2.0*PI/3) * Vy + L * omega;
  V3 = -sin(4.0*PI/3) * Vx + cos(4.0*PI/3) * Vy + L * omega;

  V1 /= r;
  V2 /= r;
  V3 /= r;

  // Convert wheel velocities to PWM (0-255) and set directions
  int pwm1_val = min(abs(V1)*255, 255);
  int pwm2_val = min(abs(V2)*255, 255);
  int pwm3_val = min(abs(V3)*255, 255);

  // if(V1 >= 0){
  //   digitalWrite(dirPin1, HIGH);
  //   analogWrite(pwmPin1, pwm1_val);
  // }else{
  //   digitalWrite(dirPin1, LOW);
  //   analogWrite(pwmPin1, pwm1_val);
  // }
  // if(V2 >= 0){
  //   digitalWrite(dirPin2, HIGH);
  //   analogWrite(pwmPin2, pwm2_val);
  // }else{
  //   digitalWrite(dirPin2, LOW);
  //   analogWrite(pwmPin2, pwm2_val);
  // }
  // if(V3 >= 0){
  //   digitalWrite(dirPin3, HIGH);
  //   analogWrite(pwmPin3, pwm3_val);
  // }else{
  //   digitalWrite(dirPin3, LOW);
  //   analogWrite(pwmPin3, pwm3_val);
  // }
  // runnig motors
  driveMotor(V1, pwmPin1, dirPin1, pwm1_val);
  driveMotor(V2, pwmPin2, dirPin2, pwm2_val);
  driveMotor(V3, pwmPin3, dirPin3, pwm3_val);


  Serial.print("Wheel velocities: V1="); Serial.print(V1);
  Serial.print(" V2="); Serial.print(V2);
  Serial.print(" V3="); Serial.println(V3);

  delay(100);
}





// digitalWrite(dirPin1, V1 >= 0 ? HIGH : LOW);
// analogWrite(pwmPin1, pwm1_val);

// digitalWrite(dirPin2, V2 >= 0 ? HIGH : LOW);
// analogWrite(pwmPin2, pwm2_val);

// digitalWrite(dirPin3, V3 >= 0 ? HIGH : LOW);
//analogWrite(pwmPin3, pwm3_val);
