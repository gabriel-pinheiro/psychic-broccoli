#include <Arduino.h>
#include <TaskManagerIO.h>
#include <DHT.h>
#include "settings.h"
#include "wifi.h"
#include "mqtt.h"

#ifdef DEBUG
#   include "debug.h"
#endif

float temperature = 0.0;
float humidity = 0.0;

DHT dht(DHT_PIN, DHT_TYPE);

void onEvent(byte* payload, unsigned int length);

void setup() {
#   ifdef SERIAL_ENABLED
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.print("\n\n\n");
#   endif

#   ifdef DEBUG
    debugSetup();
#   endif

    dht.begin();

    pinMode(LED_PIN, OUTPUT);
    connectWifi([]{
        connectMQTT(onEvent);
    });
}

void loop() {
    taskManager.runLoop();
    MQTT.loop();
#   ifdef DEBUG
    debugLoop();
#   endif
}

void onEvent(byte* payload, unsigned int length) {
    switch(payload[0]) {
        case 'C': {
            Serial.println("[INFO] Got climate request");
            temperature = dht.readTemperature();
            humidity = dht.readHumidity();
            Serial.printf("[INFO] %.2fC %.0f%\n", temperature, humidity);
            String climateResponse = String(MAC_ADDR) + ";C;" + String(temperature) + ":" + String(humidity);
            MQTT.publish(MQTT_TOPIC_UP, climateResponse.c_str());
            blink(3);
            break;
        }

        case 'P': {
            Serial.println("[INFO] Got ping request");
            // millis since start
            unsigned long now = millis();
            unsigned int freeHeap = ESP.getFreeHeap();
            Serial.printf("[INFO] %lums %u bytes\n", now, freeHeap);
            String pingResponse = String(MAC_ADDR) + ";P;" + String(now) + ":" + String(freeHeap);
            MQTT.publish(MQTT_TOPIC_UP, pingResponse.c_str());
            break;
        }

        default: {
            Serial.printf("[WARN] Got unknown packet code '%c'\n", payload[0]);
        }
    }
}
