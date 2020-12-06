#ifndef HT_MQTT_H
#define HT_MQTT_H

#include <PubSubClient.h>
#include "wifi.h"

extern PubSubClient MQTT;

#define MQTT_ID                    MAC_ADDR
#define MQTT_TOPIC_DOWN            MAC_ADDR
#define MQTT_TOPIC_UP              "main"
#define MQTT_RETRY_COOLDOWN        15000
#define MQTT_RECONNECTION_INTERVAL 500

void connectMQTT(void(onEvent)(byte *payload, unsigned int length));

#endif //HT_MQTT_H
