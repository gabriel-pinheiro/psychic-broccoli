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
        connectMQTT([](byte* payload, unsigned int length){
            if(payload[0] != 'C') {
                Serial.printf("[WARN] Got unknown packet code '%c'\n", payload[0]);
                return;
            }

            Serial.println("[INFO] Got climate request");
            temperature = dht.readTemperature();
            humidity = dht.readHumidity();
            Serial.printf("[INFO] %.2fC %.0f%\n", temperature, humidity);
            String message = String(MAC_ADDR) + ";" + String(millis()) + ":" +
                String(ESP.getFreeHeap()) + ";" + String(temperature) + ":" + String(humidity);
            MQTT.publish(MQTT_TOPIC_UP, message.c_str());
        });
    });
}

void loop() {
    taskManager.runLoop();
    MQTT.loop();
#   ifdef DEBUG
    debugLoop();
#   endif
}
