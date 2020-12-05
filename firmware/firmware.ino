#include <TaskManagerIO.h>
#include "settings.h"
#include "wifi.h"

void setup() {
#   ifdef SERIAL_ENABLED
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.print("\n\n\n");
#   endif

    pinMode(LED_PIN, OUTPUT);
    connectWifi([]{
        Serial.println("WIFI CONNECTED");
    });
}

void loop() {
    taskManager.runLoop();
}
