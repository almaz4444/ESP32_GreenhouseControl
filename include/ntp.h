#include <Arduino.h>


const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 5 * 60 * 60;
const int   daylightOffset_sec = 3600;

String getTime() {
  struct timeval tv;
  if (gettimeofday(&tv, NULL) != 0) {
    Serial.println("Failed to obtain time");
    return "NaN";
  }

  char sec[30];
  sprintf(sec, "%lld", (long long)tv.tv_sec);

  String out = String(sec) + "000";
  return out;
}

void initNTP() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}