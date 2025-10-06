//const float PI = 3.1415926535;
const float R = 0.1;   // Distance from robot center to wheel 
const float r = 0.05;  // Wheel radius 

// Max chassis speeds
const float maxVel = 0.5;     
const float maxOmega = 2.0;   

int M1_PWM = 3;
int M1_DIR = 4;

int M2_PWM = 5;
int M2_DIR = 6;

int M3_PWM = 9;
int M3_DIR = 10;


//Wheel geometry angles (120° apart)
float w1_angle = 0 * (PI / 180);
float w2_angle = 120 * (PI / 180);
float w3_angle = 240 * (PI / 180);


//Jacobian 

float J[3][3] = {
  { -sin(w1_angle),  cos(w1_angle), R },
  { -sin(w2_angle),  cos(w2_angle), R },
  { -sin(w3_angle),  cos(w3_angle), R }
};

float map1(float value, float in_min, float in_max, float out_min, float out_max) {
  return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void driveMotor(int pwmPin, int dirPin, float omega) {
  bool dir = (omega >= 0); //To check if forward or backward rotation
  int pwm = (int)(fabs(omega) / maxOmega * 255.0); // convert to pwm
  pwm = constrain(pwm, 0, 255); //pwm should not exceed 255

  if (dir) {
    digitalWrite(dirPin, HIGH);
  } else {
    digitalWrite(dirPin, LOW);
  }
  analogWrite(pwmPin, pwm);
}

void setup() {
  Serial.begin(9600);

  pinMode(M1_PWM, OUTPUT);
  pinMode(M1_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M3_PWM, OUTPUT);
  pinMode(M3_DIR, OUTPUT);

}

float v_wheels_1 = 0.0;
float v_wheels_2 = 0.0;
float v_wheels_3 = 0.0;

float Vx = 0.0;
float Vy = 0.0;
float W = 0.0;

void loop() {
  if (Serial.available() > 0) {
    Vx = Serial.parseFloat();  // joystick X (forward-backward)
    Vy = Serial.parseFloat();  // joystick Y (sideways)
    W  = Serial.parseFloat();  // joystick rotation
  }

  // Convert joystick values (-128 to 127) to real velocities
  Vx = map1(Vx, -128, 127, -maxVel, maxVel);
  Vy = map1(Vy, -128, 127, -maxVel, maxVel);
  W  = map1(W,  -128, 127, -maxOmega, maxOmega);

  //Inverse kinematics
  v_wheels_1 = (J[0][0]*Vx + J[0][1]*Vy + J[0][2]*W) / r;
  v_wheels_2 = (J[1][0]*Vx + J[1][1]*Vy + J[1][2]*W) / r;
  v_wheels_3 = (J[2][0]*Vx + J[2][1]*Vy + J[2][2]*W) / r;

  //Drive motors
  driveMotor(M1_PWM, M1_DIR, v_wheels_1);
  driveMotor(M2_PWM, M2_DIR, v_wheels_2);
  driveMotor(M3_PWM, M3_DIR, v_wheels_3);

  
  Serial.print("Vx: "); Serial.print(Vx);
  Serial.print("\tVy: "); Serial.print(Vy);
  Serial.print("\tW: "); Serial.print(W);
  Serial.print("\t| w1: "); Serial.print(v_wheels_1);
  Serial.print("\tw2: "); Serial.print(v_wheels_2);
  Serial.print("\tw3: "); Serial.println(v_wheels_3);

  delay(100);
}
