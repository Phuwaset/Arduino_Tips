#include <Keypad.h>

const byte ROWS = 4;  
const byte COLS = 4;  

char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 9, 8, 7, 6 };  
byte colPins[COLS] = { 5, 4, 3, 2 };  

char password[4];  
int i;

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  i=0;
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    Serial.println(customKey);
   
    password[i++] = customKey;

    if (i == 3) {
      
      Serial.print("PASSWORD : ");
      for (int j = 0; j < 3; j++) {
        Serial.print(password[j]);
      }
      
      Serial.println();
      if (password[0]=='1' && password[1]=='2' && password[2]=='3') {
        Serial.println("okay ");
        
      } 
      else if (password[0]=='4' && password[1]=='5' && password[2]=='6') {
        Serial.println("ok2");
        
      } 
      else if (password[0]=='A' && password[1]=='B' && password[2]=='C') {
        for (int j=0; j<3; j++) {
          digitalWrite(13, 1);
          delay(500);
          digitalWrite(13, 0);
          delay(500);
        }
      }
      else { Serial.println("fail"); }
      i = 0;  
     }
  }
}     

      

