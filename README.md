# TridentTD_ESP8266DeepSleep

A Simple Library for ESP8666' very very very long deepsleep.  
ไลบรารี่สำหรับ ESP8266 สำหรับกำหนดใช้งาน DeepSleep แบบนานๆ  
ซึ่งตามปกติจะกำหนด DeepSleep ได้มากสุดเพียงประมาณ ~71 นาทีเท่านั้น  
ให้สามารถกำหนด ได้เป็นหลายๆวัน ก็ได้  
  
ตัวอย่าง

```c
#include <TridentTD_ESP8266DeepSleep.h>

void setup() {
  Serial.begin(115200);Serial.println();
  TD_ESP.begin();   // เริ่มต้นการทำงาน DeepSleep  

  Serial.println("Good Morning...");
}

void loop() {
  // ทำงานอ่านค่า sensor ด้วย analogRead
  Serial.println(String("Analog Value : ") + String(analogRead(A0))); 


  Serial.println("DeepSleep : 10 Hours");
  TD_ESP.deepSleep(10_Hours);  // กำหนดให้ DeepSleep ไปเป็นเวลา 10 ชั่วโมงค่อยเริ่มทำงานอ่าน sensor ใหม่
}

```
