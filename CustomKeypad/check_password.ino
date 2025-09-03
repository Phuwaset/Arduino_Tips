#include <Keypad.h>
#include <string.h>

const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

char password[5];   // เก็บรหัสที่กด (เผื่อ null terminator '\0')
int i = 0;

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  Serial.begin(9600);
}

void loop() {

  char customKey = customKeypad.getKey();
  
  if (customKey) {
    Serial.println(customKey);       
    password[i++] = customKey; 
    //password[0] =1
    //password[1] =2
    //password[2] =3
    //password[] =123

    if (i == 4) {
      password[4] = '\0';  // ปิดท้าย string

      if (strcmp(password, "1234") == 0) {
        Serial.println("ok");
      } else {
        Serial.println("fail");
      }

      // แสดงรหัสที่กด
      Serial.print("You entered: ");
      Serial.println(password);

      i = 0; // รีเซ็ตเพื่อลองใหม่
    }
  }
}
