#include <Servo.h>
Servo myservo;
#include <Keypad.h>
#include <string.h>

const byte ROWS = 4;  // four rows
const byte COLS = 4;  // four columns

char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 9, 8, 7, 6 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 5, 4, 3, 2 };  //connect to the column pinouts of the keypad

char password[5];  // เก็บรหัสที่กด (เผื่อ null terminator '\0')
int i = 0;

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  myservo.attach(10);
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

    if (i == 3) {
      Serial.print("You entered: ");
      Serial.println(password);
      password[3] = '\0';  // ปิดท้าย string

      if (strcmp(password, "123") == 0) {
        Serial.println("PASS : Servo 90 ");
        delay(100);
        myservo.write(90);
      } else if (strcmp(password, "456") == 0) {
        Serial.println("PASS : Servo 0 ");
        delay(100);
        myservo.write(0);
      } else if (strcmp(password, "ABC") == 0) {
        Serial.println("PASS : Servo 180 ");
        delay(100);
        myservo.write(180);
      }



      i = 0;  // รีเซ็ตเพื่อลองใหม่
    }
  }
}
