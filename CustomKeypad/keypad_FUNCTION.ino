
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}
  
void pass_keypad(int time){
  for(int i=0;i<time;i++){
    digitalWrite(13, 1);
    delay(1000);
    digitalWrite(13, 0);
    delay(1000);
  }
}

void loop(){
  char customKey = customKeypad.getKey();
  if (customKey){
    Serial.println(customKey);
  }
  if (customKey == '1'){
    pass_keypad(1);
  }else if (customKey == '2') {
    pass_keypad(2);
  }else if (customKey == '3') {
    pass_keypad(3);
  }
} 
