#ifndef __TRIDENTTD_ESP8266_DEEPSLEEP_H__
#define __TRIDENTTD_ESP8266_DEEPSLEEP_H__

#include <Arduino.h>

union DeepSleep_t { uint32_t u32[2]; uint64_t u64; };

uint64_t operator"" _Hours(uint64_t x);
uint64_t operator"" _Minutes(uint64_t x);
uint64_t operator"" _Secs(uint64_t x);
uint64_t operator"" _Days(uint64_t x);
uint64_t operator"" _Months(uint64_t x);

class TridentTD_ESP8266DeepSleep {
  public:
    TridentTD_ESP8266DeepSleep();
    void clearDeepSleep();
    void begin();
    void deepSleep(uint64_t sec);  // กำหนด deepSleep ด้วยวินาที  ได้เป็น หลายๆ เดือนก็ได้
  private:
    DeepSleep_t _deepsleep;
};

extern TridentTD_ESP8266DeepSleep TD_ESP;

#endif
