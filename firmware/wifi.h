#ifndef HT_WIFI_H
#define HT_WIFI_H

#include <ESP8266WiFi.h>

#define RECONNECTION_COOLDOWN 30000
#define RECONNECTION_INTERVAL 500

extern String MAC_ADDR;
extern WiFiClient wifiClient;

void connectWifi(void(*onConnection)());

#endif //HT_WIFI_H
