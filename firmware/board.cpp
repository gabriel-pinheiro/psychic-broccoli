#include <Arduino.h>
#include <TaskManagerIO.h>
#include "settings.h"
#include "board.h"

void blink(int count) {
    setLed(LOW);
    for(int i = 1; i <= count; i++) {
        taskManager.scheduleOnce(200 * i, []{
            setLed(HIGH);
        }, TIME_MILLIS);
        taskManager.scheduleOnce(200 * i + 20, []{
            setLed(LOW);
        }, TIME_MILLIS);
    }
}
