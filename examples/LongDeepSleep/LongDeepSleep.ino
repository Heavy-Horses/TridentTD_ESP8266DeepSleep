#include <TridentTD_ESP8266DeepSleep.h>
#include <SimpleDHT.h>                  // https://github.com/winlinvip/SimpleDHT

int  PIN_DHT11 = 2;
SimpleDHT11 dht11;

uint8_t temperature;
uint8_t humid;

void setup() {
  Serial.begin(115200);Serial.println();

  //TD_ESP.clearDeepSleep();  // สำหรับ clear ข้อมูล DeepSleep เดิมออกไป
  TD_ESP.begin();   // เริ่มต้นการทำงาน DeepSleep
  
  Serial.println("Good Morning");
  delay(1000);
}

void loop() {
  if( dht11.read( PIN_DHT11, &temperature, &humid, NULL)) {
    Serial.print("Read DHT11 failed.");
    return;
  }

  Serial.println(String("Temp  : ") + String( temperature ) + String(" C")); 
  Serial.println(String("Humid : ") + String( humid ) + String(" %")); 


  Serial.println("DeepSleep 12 Hours 30 minutes 10 secs");
  TD_ESP.deepSleep(12_Hours + 30_Minutes + 10_Secs);  // ให้ deepsleep ไปเป็นเวลา 12 ชม. 30 นาที 10 วินาที

  // TD_ESP.deepSleep(3_Days);      // ให้ deepsleep ไปเป็นเวลา 3 วัน
  // TD_ESP.deepSleep(10_Hours);    // ให้ deepsleep ไปเป็นเวลา 10 ชั่วโมง
  // TD_ESP.deepSleep(30_Minutes);  // ให้ deepsleep ไปเป็นเวลา 30 นาที

}


