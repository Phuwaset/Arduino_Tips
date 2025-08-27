int POT_ = A3;
const int LED_ = 13;
#define led10 10
void setup() {
  Serial.begin(9600);
  pinMode(LED_, OUTPUT);
  pinMode(led10, OUTPUT);
}

void loop() {
  int potValue = analogRead(POT_);

  int voltage = (potValue * 5.0 / 1023.0);
  if (voltage >= 4) {Serial.print("Over Voltage ");}
  float temp = (22.5 *voltage) -10;

  if (voltage > 4) {
    temp = 80;
    Serial.print("Over voltage");
  }else if (voltage < 0){
    temp = -10;
  }
  Serial.print("Potentiometer: ");
  Serial.print(potValue);
  Serial.print("   > voltage: ");
  Serial.print(voltage, 1); 
  Serial.print("V");     
  Serial.print("  Temperatrue : ");
  Serial.print(temp,2);
  Serial.println("  C");

  delay(100); 
}

                                                                                                              
