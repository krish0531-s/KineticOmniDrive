
const float  PI = 3.1415926535;
const int RPM = 50;

// Setting up geometry
int Motor1_in1 = 13; //input4
int Motor1_in2 = 12; //input3
int Motor1_enable = 11;

int Motor2_in1 = 8; //input4
int Motor2_in2 = 7; // input3
int Motor2_enable = 9;

int Motor3_in1 = 4; //input2
int Motor3_in2 = 5; //input 1
int Motor3_enable = 10;


float R = 0.1; //From centre of wheel to ground
float r = 0.05; //Radius of wheel

float w1_angle = 0*(PI/180);
float w2_angle = 120*(PI/180);
float w3_angle = 240*(PI/180);

float J[3][3] = {
  {-sin(w1_angle), cos(w1_angle), R},
  {-sin(w2_angle), cos(w2_angle), R},
  {-sin(w3_angle), cos(w3_angle), R}
};

int map1(float value, float inp_start, float inp_end, float out_start, float out_end){ //Custom map function to deal with floating integers
    
    float out_diff = out_end-out_start;
    float inp_diff = inp_end-inp_start;
    float val = value * (out_diff/inp_diff);

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

float v_wheels_1 = 0.0;
float v_wheels_2 = 0.0; //Wheel velocities
float v_wheels_3 = 0.0;

float Vx = 0.0;
float Vy = 0.0; //Chasis speeds in x, y and angular velocity around centre
float W = 0.0;  //Meter/second Metre/second Radian/second

void loop() {
  if(Serial.available()>0){
    Vx = Serial.parseFloat(); //Let it be left joystick
    Vy = Serial.parseFloat(); //Let it be right Joystick
    W = Serial.parseFloat();
  }

  v_wheels_1 = ((J[0][0]*Vx + J[0][1]*Vy + J[0][2]*W)/r)*60*(2/PI);
  v_wheels_2 = ((J[1][0]*Vx + J[1][1]*Vy + J[1][2]*W)/r)*60*(2/PI); //rad/s to RPM
  v_wheels_3 = ((J[2][0]*Vx + J[2][1]*Vy + J[2][2]*W)/r)*60*(2/PI);

  
}
