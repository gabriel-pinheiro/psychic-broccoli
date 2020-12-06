#include <Arduino.h>
#include <TaskManagerIO.h>
#include "settings.h"
#include "wifi.h"
#include "mqtt.h"

#ifdef DEBUG
#   include "debug.h"
#endif

void setup() {
#   ifdef SERIAL_ENABLED
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.print("\n\n\n");
#   endif

#   ifdef DEBUG
    debugSetup();
#   endif

    pinMode(LED_PIN, OUTPUT);
    connectWifi([]{
        connectMQTT([](byte* payload, unsigned int length){
            Serial.println("Received MQTT message");
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
