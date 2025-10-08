#include <Encoder.h>

Encoder myEnc(20, 21);   // Encoder connected to pins 2 and 3

int Lpwm = 0;
int Rpwm = 1;


// Adjust this based on your measurement
const float PPR = 703.0;   // Pulses Per Revolution (from your test)
unsigned long lastTime = 0;
long lastTicks = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Measuring live RPM...");
}
int PWM = 0;
void loop() {

  if(Serial.available()>0){
    PWM = Serial.parseInt();

  }
  analogWrite(Lpwm, PWM);

  Serial.print("Pwm: ");Serial.println(PWM);

  unsigned long currentTime = millis();
  long currentTicks = myEnc.read();

  // Calculate every 100 ms (0.1 second)
  if (currentTime - lastTime >= 100) {
    long deltaTicks = currentTicks - lastTicks;           // ticks since last check
    float deltaTime = (currentTime - lastTime) / 1000.0;  // convert ms → seconds

    // Calculate RPM
    float revolutions = deltaTicks / PPR;   // revolutions during time window
    float rpm = (revolutions / deltaTime) * 60.0;

    Serial.print("RPM: ");
    Serial.println(rpm, 2);

    // Update old values
    lastTicks = currentTicks;
    lastTime = currentTime;
  }
}
