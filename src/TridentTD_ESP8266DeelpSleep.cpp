#include "TridentTD_ESP8266DeepSleep.h"
#include <FS.h>

#define DEEPSLEEP_INTERVAL    3600  // ห้ามปรับค่า 

uint64_t operator"" _Hours(uint64_t x)    { return x * 3600; }
uint64_t operator"" _Minutes(uint64_t x)  { return x * 60; }
uint64_t operator"" _Days(uint64_t x)     { return x * 86400; }
uint64_t operator"" _Months(uint64_t x)   { return x * 86400*30; }
uint64_t operator"" _Secs(uint64_t x)     { return x;}

static DeepSleep_t loadDeepSleep() {
  DeepSleep_t buf; buf.u64=0;
  if(!SPIFFS.exists("/DeepSleep.txt")) return buf;
  File DeepSleepFile = SPIFFS.open("/DeepSleep.txt", "r");
  if(!DeepSleepFile) return buf;
  uint64_t data;
  DeepSleepFile.read((uint8_t*)&data,sizeof(int64_t));
  DeepSleepFile.close();
  buf.u64 = data;
  return buf;
}

static bool saveDeepSleep(uint64_t sec){
  if(SPIFFS.exists("/DeepSleep.txt"))  SPIFFS.remove("/DeepSleep.txt");
  File DeepSleepFile = SPIFFS.open("/DeepSleep.txt", "w");
  if(!DeepSleepFile) return false;
  DeepSleepFile.write((uint8_t*)&sec,sizeof(int64_t));
  DeepSleepFile.close();
//  Serial.println("[DeepSleep] save done!");
  return true;
}

static void ESP_setSleep(uint64_t sec) {  // 0-3600 secs
  if(sec > DEEPSLEEP_INTERVAL) sec = DEEPSLEEP_INTERVAL;
  ESP.deepSleep(sec*1000000); //Process
}

//-------------------------------------------------------

TridentTD_ESP8266DeepSleep::TridentTD_ESP8266DeepSleep(){
}

void TridentTD_ESP8266DeepSleep::begin(){
  if(!SPIFFS.begin()) { Serial.println("[DeepSleep] ERROR : can't init SPIFFS"); return; }
  _deepsleep = loadDeepSleep();
//  Serial.printf("[DeepSleep] left : %d\n", _deepsleep.u32[0]);

  if( _deepsleep.u64 > 0) {  
    Serial.printf("[DeepSleep] left_time : %d secs ...DeepSleep Again\n", _deepsleep.u32[0]);
    this->deepSleep( _deepsleep.u64 );
  }
}

void TridentTD_ESP8266DeepSleep::deepSleep(uint64_t sec){
  if(sec == 0) return;
  
  if( sec > DEEPSLEEP_INTERVAL) {
    sec -=DEEPSLEEP_INTERVAL;
    saveDeepSleep( sec );
    ESP_setSleep(DEEPSLEEP_INTERVAL);
  }else{
    this->clearDeepSleep();
    ESP_setSleep(sec);
  }
}

void TridentTD_ESP8266DeepSleep::clearDeepSleep(){
  if(SPIFFS.exists("/DeepSleep.txt"))  SPIFFS.remove("/DeepSleep.txt");
}

TridentTD_ESP8266DeepSleep TD_ESP;
