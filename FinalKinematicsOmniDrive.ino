#include <PS4BT.h>
#include <usbhub.h>


USB Usb;
BTD Btd(&Usb);
PS4BT PS4(&Btd);


//const float PI = 3.1415926535;
const float R_wheel = 0.1;     // distance from center to wheel (m)
const float r_wheel = 0.05;    // wheel radius (m)
const float maxVel = 0.5;     // max linear velocity (m/s)
const float maxOmega = 2.0;   // max angular velocity (rad/s)

int M1_PWM = 3;
int M1_DIR = 4;

int M2_PWM = 5;
int M2_DIR = 6;

int M3_PWM = 9;
int M3_DIR = 10;

//
float w1_angle = 0 * (PI / 180);
float w2_angle = 120 * (PI / 180);
float w3_angle = 240 * (PI / 180);

// Jacobian 
float J[3][3] = {
  {-sin(w1_angle), cos(w1_angle), R_wheel},
  {-sin(w2_angle), cos(w2_angle), R_wheel},
  {-sin(w3_angle), cos(w3_angle), R_wheel}
};


float Vx = 0.0;
float Vy = 0.0;
float W  = 0.0;

float v_wheels_1 = 0.0;
float v_wheels_2 = 0.0;
float v_wheels_3 = 0.0;

float map1(float value, float in_min, float in_max, float out_min, float out_max) {
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void driveMotor(int pwmPin, int dirPin, float omega) {
    bool dir = (omega >= 0);
    int pwm = (int)(fabs(omega) / maxOmega * 255.0);
    pwm = constrain(pwm, 0, 255);

    if (dir) {
        digitalWrite(dirPin, HIGH);
    } else {
        digitalWrite(dirPin, LOW);
    }
    analogWrite(pwmPin, pwm);
}

void setup() {
    Serial.begin(115200);

    pinMode(M1_PWM, OUTPUT);
    pinMode(M1_DIR, OUTPUT);
    pinMode(M2_PWM, OUTPUT);
    pinMode(M2_DIR, OUTPUT);
    pinMode(M3_PWM, OUTPUT);
    pinMode(M3_DIR, OUTPUT);

    Usb.Init();
    Serial.println("Waiting for PS4 controller...");
}

void loop() {
    Usb.Task();

    if (PS4.connected()) {
        // Read joysticks (0-255)
        int lx = PS4.getAnalogHat(LeftHatX);
        int ly = PS4.getAnalogHat(LeftHatY);
        int rx = PS4.getAnalogHat(RightHatX);

        // Convert to centered range -128 to 127
        Vx = lx - 128; // left stick X
        Vy = 128 - ly; // left stick Y (invert Y)
        W  = rx - 128; // right stick X

        // Map joystick to real velocities
        Vx = map1(Vx, -128, 127, -maxVel, maxVel);
        Vy = map1(Vy, -128, 127, -maxVel, maxVel);
        W  = map1(W, -128, 127, -maxOmega, maxOmega);

        //Inverse Kinematics 
        v_wheels_1 = (J[0][0]*Vx + J[0][1]*Vy + J[0][2]*W) / r_wheel;
        v_wheels_2 = (J[1][0]*Vx + J[1][1]*Vy + J[1][2]*W) / r_wheel;
        v_wheels_3 = (J[2][0]*Vx + J[2][1]*Vy + J[2][2]*W) / r_wheel;

        //Drive Motor
        driveMotor(M1_PWM, M1_DIR, v_wheels_1);
        driveMotor(M2_PWM, M2_DIR, v_wheels_2);
        driveMotor(M3_PWM, M3_DIR, v_wheels_3);

        Serial.print("Vx: "); Serial.print(Vx);
        Serial.print(" Vy: "); Serial.print(Vy);
        Serial.print(" W: "); Serial.print(W);
        Serial.print(" | w1: "); Serial.print(v_wheels_1);
        Serial.print(" w2: "); Serial.print(v_wheels_2);
        Serial.print(" w3: "); Serial.println(v_wheels_3);
    }
}
