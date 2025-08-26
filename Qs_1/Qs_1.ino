#define LED_GREEN_ 8
#define LED_YELLOW_ 9
#define LED_RED_ 10
#define BUTTON_Switch_ 2

#define STATE_GREEN_ 0
#define STATE_YELLOW_ 1
#define STATE_RED_ 2

int currentState = STATE_RED_;  //Start State_RED

unsigned long previousMillis = 0;

// Interval/ช่วงเวลา unit:ms
const long greenInterval = 5000;
const long yellowTnterval = 2000;
const long redInterval = 5000;

void setup() {
  Serial.begin(115200);
  pinMode(LED_GREEN_, OUTPUT);
  pinMode(LED_YELLOW_, OUTPUT);
  pinMode(LED_RED_, OUTPUT);
  pinMode(BUTTON_Switch_, INPUT_PULLUP);
}

void Set_Light(bool green, bool yellow, bool red) {
  digitalWrite(LED_GREEN_, green);
  digitalWrite(LED_YELLOW_, yellow);
  digitalWrite(LED_RED_, red);
}

void loop() {
  unsigned long currentMillis = millis();

  switch (currentState) {
    case STATE_GREEN_:
      Set_Light(1, 0, 0);
      if (currentMillis - previousMillis >= greenInterval) {
        currentState = STATE_YELLOW_;
        previousMillis = currentMillis;
      }
      break;
    case STATE_YELLOW_:
      Set_Light(0, 1, 0);
      if (currentMillis - previousMillis >= yellowTnterval) {
        currentState = STATE_RED_;
        previousMillis = currentMillis;
      }
      break;
    case STATE_RED_:
      Set_Light(0, 0, 1);
      if (currentMillis - previousMillis >= redInterval) {
        currentState = STATE_GREEN_;
        previousMillis = currentMillis;
      }
      break;
  }
  int buttonSate_ = digitalRead(BUTTON_Switch_);
  if (buttonSate_ == 1 & currentState == STATE_GREEN_) {
    Serial.println("Button Pressed! Changing to Yellow.");
    currentState = STATE_YELLOW_;
    previousMillis = currentMillis;
  }
}
