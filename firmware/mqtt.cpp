#include <Arduino.h>
#include <TaskManagerIO.h>
#include <PubSubClient.h>
#include "mqtt.h"
#include "wifi.h"
#include "board.h"

PubSubClient MQTT(wifiClient);

unsigned long int lastMqttAttempt = 0;
taskid_t mqttTask = 0;

void assertMQTTConnection() {
    if(MQTT.connected()) {
        return;
    }

    if(millis() - lastMqttAttempt < MQTT_RETRY_COOLDOWN && lastMqttAttempt != 0) {
        return;
    }
    lastMqttAttempt = millis();

    Serial.println("Connecting to MQTT");
    setLed(HIGH);

    if (MQTT.connect(MQTT_ID.c_str())) {
        MQTT.subscribe(MQTT_TOPIC_DOWN.c_str());
        Serial.println("MQTT connected");
    } else {
        Serial.println("Unable to connect to MQTT");
    }
    setLed(LOW);
}

void connectMQTT(void(onEvent)(byte *payload, unsigned int length)) {
    if(mqttTask) {
        return;
    }

    MQTT.setServer(MQTT_HOST, MQTT_PORT);
    MQTT.setCallback([onEvent](char *topic, byte *payload, unsigned int length) {
        onEvent(payload, length);
    });

    taskManager.execute(assertMQTTConnection);
    mqttTask = taskManager.scheduleFixedRate(MQTT_RECONNECTION_INTERVAL, assertMQTTConnection, TIME_MILLIS);
}
