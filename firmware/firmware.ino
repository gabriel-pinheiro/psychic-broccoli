#include <TaskManagerIO.h>
#include "settings.h"

void setup() {
#   ifdef SERIAL_ENABLED
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.print("\n\n\n");
#   endif

    taskManager.scheduleFixedRate(1, []{
        Serial.println("Hi :)");
    }, TIME_SECONDS);
}

void loop() {
    taskManager.runLoop();
}
