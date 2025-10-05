//const float PI = 3.1415926535;
const int RPM = 50;
const float maxVel = 0.5;
const float maxOmega = 2.0;

int Motor1_in1 = 13;
int Motor1_in2 = 12;
int Motor1_enable = 11;

int Motor2_in1 = 8;
int Motor2_in2 = 7;
int Motor2_enable = 9;

int Motor3_in1 = 4;
int Motor3_in2 = 5;
int Motor3_enable = 10;

float R = 0.1; 
float r = 0.05; 

float w1_angle = 0 * (PI / 180);
float w2_angle = 120 * (PI / 180);
float w3_angle = 240 * (PI / 180);

float J[3][3] = {
  {-sin(w1_angle), cos(w1_angle), R},
  {-sin(w2_angle), cos(w2_angle), R},
  {-sin(w3_angle), cos(w3_angle), R}
};

float v_wheels_1 = 0.0;
float v_wheels_2 = 0.0;
float v_wheels_3 = 0.0;

float Vx = 0.0;
float Vy = 0.0;
float W = 0.0;

float MAX_OMEGA = (2 * PI * RPM) / 60.0;  // Convert max RPM to rad/s

float map1(float value, float inp_start, float inp_end, float out_start, float out_end) {
  float out_diff = out_end - out_start;
  float inp_diff = inp_end - inp_start;
  float val = (value - inp_start) * (out_diff / inp_diff) + out_start;
  return val;
}

void setup() {
  Serial.begin(9600);
  pinMode(Motor1_in1, OUTPUT);
  pinMode(Motor1_in2, OUTPUT);
  pinMode(Motor1_enable, OUTPUT);
  pinMode(Motor2_in1, OUTPUT);
  pinMode(Motor2_in2, OUTPUT);
  pinMode(Motor2_enable, OUTPUT);
  pinMode(Motor3_in1, OUTPUT);
  pinMode(Motor3_in2, OUTPUT);
  pinMode(Motor3_enable, OUTPUT);
}

void driveMotor(int in1, int in2, int en, float omega) {
  bool dir = (omega >= 0);
  int pwm = (int)(fabs(omega) / MAX_OMEGA * 255.0);
  pwm = constrain(pwm, 0, 255);

  digitalWrite(in1, dir ? HIGH : LOW);
  digitalWrite(in2, dir ? LOW : HIGH);
  analogWrite(en, pwm);
}

void loop() {
  if (Serial.available() > 0) {
    Vx = Serial.parseFloat();
    Vy = Serial.parseFloat();  //Assume as joystick inputs for now
    W  = Serial.parseFloat();
  }

  
  Vx = map1(Vx, -128, 127, -maxVel, maxVel);
  Vy = map1(Vy, -128, 127, -maxVel, maxVel); // Convert joystick to real velocities
  W  = map1(W, -128, 127, -maxOmega, maxOmega);

  
  v_wheels_1 = (J[0][0] * Vx + J[0][1] * Vy + J[0][2] * W) / r;
  v_wheels_2 = (J[1][0] * Vx + J[1][1] * Vy + J[1][2] * W) / r; // Inverse kinematics
  v_wheels_3 = (J[2][0] * Vx + J[2][1] * Vy + J[2][2] * W) / r;

  driveMotor(Motor1_in1, Motor1_in2, Motor1_enable, v_wheels_1);
  driveMotor(Motor2_in1, Motor2_in2, Motor2_enable, v_wheels_2);
  driveMotor(Motor3_in1, Motor3_in2, Motor3_enable, v_wheels_3);
}
