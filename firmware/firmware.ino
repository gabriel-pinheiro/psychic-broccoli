#include <Arduino.h>
#include <TaskManagerIO.h>
#include "settings.h"
#include "wifi.h"

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
        Serial.println("WIFI CONNECTED");
    });
}

void loop() {
    taskManager.runLoop();
#   ifdef DEBUG
    debugLoop();
#   endif
}
