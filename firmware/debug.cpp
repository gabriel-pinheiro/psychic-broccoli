#include <Arduino.h>
#include <TaskManagerIO.h>
#include "debug.h"

unsigned long int lastLoopMillis = 0;
void debugLoop() {
    unsigned long int currentMillis = millis();
    int deltaT = currentMillis - lastLoopMillis;
    lastLoopMillis = currentMillis;

    if(deltaT <= 10) {
        return;
    }

    Serial.print("[WARN] Loop took ");
    Serial.print(deltaT);
    Serial.println("ms to run");
}


unsigned int lastMemory = 0;
void monitorMemory() {
    unsigned int currentMemory = ESP.getFreeHeap();

    if(currentMemory != lastMemory && lastMemory != 0) {
        Serial.print("[INFO] Free heap changed from ");
        Serial.print(lastMemory);
        Serial.print("b to ");
        Serial.print(currentMemory);
        Serial.println("b");
    }

    lastMemory = currentMemory;
}

void debugSetup() {
    taskManager.scheduleFixedRate(500, monitorMemory, TIME_MILLIS);
}
