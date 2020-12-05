#ifndef HT_WIFI_H
#define HT_WIFI_H

#define WIFI_SSID     "-"
#define WIFI_PASSWORD "-"
#define RECONNECTION_COOLDOWN 15000
#define RECONNECTION_INTERVAL 500

extern String MAC_ADDR;

void connectWifi(void(*onConnection)());

#endif //HT_WIFI_H
