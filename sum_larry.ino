
#include <Keypad.h>

const byte ROWS = 4;  //four rows
const byte COLS = 4;  //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 9, 8, 7, 6 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 5, 4, 3, 2 };  //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

char password[5];  // เก็บรหัสที่กด (เผื่อ null terminator '\0')
int i = 0;

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    Serial.println(customKey);
    password[i++] = customKey;

    if (i == 4) {
      delay(100);
      // password[4] = '\0';
      for (int j = 0; j < 4; j++) {
        
        Serial.println(j);
        delay(100);
        Serial.println(password[j]);
        i = 0;
      }
    }
  }
}

// OUTPUT

// 14:34:57.070 -> 1
// 14:34:58.297 -> 2
// 14:34:59.396 -> 3
// 14:35:00.666 -> 4
// 14:35:00.886 -> --- 
// 14:35:00.886 -> 1
// 14:35:00.972 -> --- 
// 14:35:00.972 -> 2
// 14:35:01.099 -> --- 
// 14:35:01.099 -> 3
// 14:35:01.191 -> --- 
// 14:35:01.191 -> 4
