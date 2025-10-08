#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <time.h>

// ===== Wi-Fi & LINE config =====
const char* ssid = "X50s._Phu";       
const char* password = "p0000000"; 
#define CHANNEL_ACCESS_TOKEN "sdEIOvZPeIu1MlYVJSuZRapZiIuVavd8vvK/twAC5hcClR4cewyfgoI0kfTzlYxY5kRowaVxaO0c6BSHoxfGG1egPk0MbdGnxm5a8iavOFUXO46Bi3wAUZbrlJOI09Ql41fkQ34fRQmbIfefWuCyBQdB04t89/1O/w1cDnyilFU="
//#define CHANNEL_ACCESS_TOKEN "YOUR_LONG_LIVED_CHANNEL_ACCESS_TOKEN"   // << paste your token


const char* GROUP_ID = "Ue587e542c744f2de308985beac70f92d";

const int analogPin = 34;

// Reusable secure client for all requests (must be global to avoid deallocation/reboot issues)
WiFiClientSecure client;

// ---------------- Time sync (TLS needs correct time) ----------------
void setupTime() {
  configTime(7 * 3600, 0, "pool.ntp.org", "time.nist.gov");  // GMT+7
  time_t now = time(nullptr);
  int retry = 0;
  while (now < 1700000000 && retry < 60) {  // wait until year >= 2023
    delay(250);
    now = time(nullptr);
    retry++;
  }
  Serial.printf("Time synced: %s\n", ctime(&now));
}

// ---------------- Helper: HTTP POST to LINE push endpoint ----------------
bool httpPostLinePush(const String& jsonPayload) {
  HTTPClient https;
  if (!https.begin(client, "https://api.line.me/v2/bot/message/push")) {
    Serial.println("[httpPostLinePush] https.begin failed");
    return false;
  }
  https.addHeader("Content-Type", "application/json");
  https.addHeader("Authorization", String("Bearer ") + CHANNEL_ACCESS_TOKEN);

  int code = https.POST(jsonPayload);
  String resp = https.getString();
  https.end();

  Serial.printf("[httpPostLinePush] code=%d\n", code);
  Serial.println(resp);
  return (code >= 200 && code < 300);
}

// ---------------- API: Send text only ----------------
bool linePushText(const String& to, const String& text) {
  String payload = String("{\"to\":\"") + to + "\",\"messages\":[{\"type\":\"text\",\"text\":\"" + text + "\"}]}";
  return httpPostLinePush(payload);
}

// ---------------- API: Send text + sticker ----------------
bool linePushTextWithSticker(const String& to,
                             const String& text,
                             const String& packageId,
                             const String& stickerId) {
  // messages: [ text , sticker ]
  String payload = String("{\"to\":\"") + to + "\",\"messages\":[{\"type\":\"text\",\"text\":\"" + text + "\"},"
                                                                                                          "{\"type\":\"sticker\",\"packageId\":\""
                   + packageId + "\",\"stickerId\":\"" + stickerId + "\"}]}";
  return httpPostLinePush(payload);
}

// ---------------- Setup & Demo ----------------
void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }

  Serial.println("\nConnecting Wi-Fi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.printf("\nWiFi connected. IP: %s\n", WiFi.localIP().toString().c_str());

  setupTime();

  // Use ONLY one of these:
  client.setInsecure();  // โ ๏ธ for quick testing only
  
  Serial.println("Setup complete. Starting main loop...");

//  // Demo sends
  linePushText(GROUP_ID, "123");
  //delay(2000);
  linePushTextWithSticker(GROUP_ID, "abc", "1070", "17841");
}

// ---------------- Main Loop ----------------
void loop() {
 int analogValue = analogRead(analogPin);

 Serial.printf("Analog value from GPIO34: %d\n", analogValue);

 String message = "Analog " + String(analogValue);

 linePushText(GROUP_ID, message);

 delay(5000);
}
