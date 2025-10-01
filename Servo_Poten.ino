

#include <Servo.h>

Servo myServo; 
const int Poten_Pin = A1;       
const int servoPin = 9; 
const int buttonPin = 2;       
const int LED7 = 7;
const int LED4 = 4;

int buttonState = 1;   
int state = 0; 
int state2 = 0;

unsigned long prevMillis = 0;
unsigned long prevMillis2 = 0;
const long interval_1 = 1000;  
const long interval_2 = 3000; 

void setup() {
  Serial.begin(9600); 
  myServo.attach(servoPin);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED7,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(13,OUTPUT);
  myServo.write(0);
  
}

void loop() {
  int potValue = analogRead(Poten_Pin);           // อ่านค่า 0-1023
  int angle = map(potValue, 0, 1023, 0, 180);     // แปลงเป็น 0-180°

  
  if (angle >= 0 && angle <= 90) {       
    myServo.write(180);
    Serial.println("Pot=90 Servo=180");
  } 
  else if (angle >= 90 && angle <=180) {
    myServo.write(0);
    Serial.println("Pot=180 Servo=0");
  } 
  else {
    myServo.write(angle);  
  }
  
  delay(50);

  buttonState = digitalRead(buttonPin);

  if(buttonState == 0){

     digitalWrite(13,1);
     delay(10);
  }else {
     digitalWrite(13,0);
     delay(10);
  }
  
  
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis >= interval_1) {
    prevMillis = currentMillis;
    state = !state;
    digitalWrite(LED7, state); 
  } 
 if (currentMillis - prevMillis2 >= interval_2) {
    prevMillis2 = currentMillis;
    state2 = !state2;
    digitalWrite(LED4, state2);
  }
}

