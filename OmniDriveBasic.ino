// C++ code
//
int motor1_in_1 = 13; //input4
int motor1_in_2 = 12; //input3
int motor1_enable = 11;

int motor2_in_1 = 8; //input4
int motor2_in_2 = 7; // input3
int motor2_enable = 9;

int motor3_in_1 = 4; //input2
int motor3_in_2 = 5; //input 1
int motor3_enable = 10;
void setup()
{
  Serial.begin(9600);
  
  pinMode(motor1_in_1, OUTPUT);
  pinMode(motor1_in_2, OUTPUT);
  pinMode(motor1_enable, OUTPUT);
  
  pinMode(motor2_in_1, OUTPUT);
  pinMode(motor2_in_2, OUTPUT);
  pinMode(motor2_enable, OUTPUT);
  
  pinMode(motor3_in_1, OUTPUT);
  pinMode(motor3_in_2, OUTPUT);
  pinMode(motor3_enable, OUTPUT);
  
}
void forward(){
  digitalWrite(motor1_in_2, LOW);
  digitalWrite(motor1_in_1, HIGH);
  analogWrite(motor1_enable, 0);
  
  digitalWrite(motor2_in_1, HIGH);
  digitalWrite(motor2_in_2, LOW); //Clockwise
  analogWrite(motor2_enable, 255); 
  
  digitalWrite(motor3_in_1, HIGH);
  digitalWrite(motor3_in_2, LOW); //
  analogWrite(motor3_enable, 255);
}
void backward(){
  digitalWrite(motor1_in_2, LOW);
  digitalWrite(motor1_in_1, HIGH);
  analogWrite(motor1_enable, 0);
  
  digitalWrite(motor2_in_2, HIGH);
  digitalWrite(motor2_in_1, LOW);
  analogWrite(motor2_enable, 255);
  
  digitalWrite(motor3_in_2, HIGH);
  digitalWrite(motor3_in_1, LOW);
  analogWrite(motor3_enable, 255);
}
void left(){
  digitalWrite(motor1_in_2, LOW);
  digitalWrite(motor1_in_1, HIGH);
  analogWrite(motor1_enable, 255);
  
  digitalWrite(motor2_in_2, HIGH);
  digitalWrite(motor2_in_1, LOW); //anticlockwise
  analogWrite(motor2_enable, 255);
  
  digitalWrite(motor3_in_2, HIGH);
  digitalWrite(motor3_in_1, LOW);
  analogWrite(motor3_enable, 255);
}
void right(){
  digitalWrite(motor1_in_1, LOW);
  digitalWrite(motor1_in_2, HIGH); //clockwise
  analogWrite(motor1_enable, 255);
  
  digitalWrite(motor2_in_1, HIGH);
  digitalWrite(motor2_in_2, LOW);
  analogWrite(motor2_enable, 255);
  
  digitalWrite(motor3_in_1, HIGH);
  digitalWrite(motor3_in_2, LOW);
  analogWrite(motor3_enable, 255);
}
void southEast(){
  digitalWrite(motor1_in_1, LOW);
  digitalWrite(motor1_in_2, HIGH); //clockwise
  analogWrite(motor1_enable, 255);
  
  digitalWrite(motor2_in_2, HIGH);
  digitalWrite(motor2_in_1, LOW); //anticlockwise
  analogWrite(motor2_enable, 255);
  
  digitalWrite(motor3_in_2, LOW);
  digitalWrite(motor3_in_1, HIGH);
  analogWrite(motor3_enable, 0);
}
void northWest(){
  digitalWrite(motor1_in_2, LOW);
  digitalWrite(motor1_in_1, HIGH); //clockwise
  analogWrite(motor1_enable, 255);
  
  digitalWrite(motor2_in_1, HIGH);
  digitalWrite(motor2_in_2, LOW); //anticlockwise
  analogWrite(motor2_enable, 255);
  
  digitalWrite(motor3_in_2, LOW);
  digitalWrite(motor3_in_1, HIGH);
  analogWrite(motor3_enable, 0);
}
void northEast(){
  digitalWrite(motor1_in_2, LOW);
  digitalWrite(motor1_in_1, HIGH); //clockwise
  analogWrite(motor1_enable, 255);
  
  digitalWrite(motor2_in_1, HIGH);
  digitalWrite(motor2_in_2, LOW); 
  analogWrite(motor2_enable, 0);
}
void southWest(){
  digitalWrite(motor1_in_2, HIGH);
  digitalWrite(motor1_in_1, LOW); //clockwise
  analogWrite(motor1_enable, 255);
  
  digitalWrite(motor2_in_1, LOW);
  digitalWrite(motor2_in_2, HIGH); 
  analogWrite(motor2_enable, 0);
}
void stop(){
  digitalWrite(motor1_in_2, LOW);
  digitalWrite(motor1_in_1, HIGH); 
  analogWrite(motor1_enable, 0);
  
  digitalWrite(motor2_in_1, HIGH);
  digitalWrite(motor2_in_2, LOW); 
  analogWrite(motor2_enable, 0);
  
  digitalWrite(motor3_in_2, LOW);
  digitalWrite(motor3_in_1, HIGH);
  analogWrite(motor3_enable, 0);
}
void loop()
{
  char dir = 'p';
  if(Serial.available() > 0){
    dir = Serial.read();
  }
  if(dir == 'w'){
    forward();
    Serial.println("Forward");
  }
  else if(dir == 'a'){
    left();
    Serial.println("Left");
  }
  else if(dir == 'd'){
    right();
    Serial.println("Right");
  }
  else if(dir == 's'){
    backward();
    Serial.println("Backward");
  }
  else if(dir == 'c'){
    southEast();
    Serial.println("SouthEast");
  }
  else if(dir == 'q'){
    northWest();
    Serial.println("NorthWestz");
  }
  else if(dir == 'z'){
    southWest();
    Serial.println("SouthWest");
  }
  else if(dir == 'p'){
    stop();
    Serial.println("Stopped");
  }
  
}