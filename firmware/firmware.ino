#include <TaskManagerIO.h>
#include "settings.h"
#include "board.h"

void setup() {
#   ifdef SERIAL_ENABLED
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.print("\n\n\n");
#   endif

    pinMode(LED_PIN, OUTPUT);
    taskManager.scheduleFixedRate(2, []{
        blink(3);
    }, TIME_SECONDS);
}

void loop() {
    taskManager.runLoop();
}
