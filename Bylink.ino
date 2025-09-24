#define BLYNK_TEMPLATE_ID "TMPL6JmLtUbAx"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN  "PvMzQKZs5RctebN3eLKrNz2AaFU9KVgv"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "X50s._Phu";     
char pass[] = "p0000000";      

BlynkTimer timer;

#define RELAY_PIN 2     // ขาเอาต์พุต (ควบคุมด้วยปุ่ม V0)
#define ADC_PIN   34    // ขา ADC input

// ฟังก์ชันส่งค่า ADC ไปที่ Virtual Pin V6
void sendADC()
{
  int adcValue = analogRead(ADC_PIN); // อ่านค่า ADC (0-4095)
  Blynk.virtualWrite(V6, adcValue);   // ส่งค่าไปยัง Blynk (V6)
  Serial.print("ADC Value: ");
  Serial.println(adcValue);
}

// ฟังก์ชันควบคุม GPIO2 ด้วยปุ่ม V0
BLYNK_WRITE(V0)
{
  int value = param.asInt();
  digitalWrite(RELAY_PIN, value);  
  Serial.print("Button Control (GPIO2): ");
  Serial.println(value);
}

void setup()
{
  Serial.begin(115200);

  // เริ่มเชื่อมต่อ WiFi และ Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // ตั้งขา GPIO
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // ปิดค่าเริ่มต้น

  // ตั้งให้ส่งค่า ADC ทุก 1 วินาที
  timer.setInterval(1000L, sendADC);
}

void loop()
{
  Blynk.run();
  timer.run();
}
