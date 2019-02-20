#include <TridentTD_ESP8266DeepSleep.h>

void setup() {
  Serial.begin(115200);Serial.println();
  TD_ESP.begin();   // เริ่มต้นการทำงาน DeepSleep  

  Serial.println("Good Morning...");
}

void loop() {
  Serial.println(String("Analog Value : ") + String(analogRead(A0))); 

  Serial.println("DeepSleep : 20 secs");
  TD_ESP.deepSleep(20_Secs);  // กำหนดให้ DeepSleep ไปเป็นเวลา 20 วินาทีค่อยเริ่มทำงานใหม่
}

