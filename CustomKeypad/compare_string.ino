
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

// char password[5];  // เก็บรหัสที่กด (เผื่อ null terminator '\0')
// int i = 0;

void loop() {
  char customKey = customKeypad.getKey();

  char pass1[] = "1234";
  char pass2[] = "1234";
  char pass3[] = "5678";

  if (strcmp(pass1, pass2) == 0) {
    Serial.println("Seem [data]");
  } else {
    Serial.println("Not seem [data]");
  }
}

