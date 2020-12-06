#ifndef HT_BOARD_H
#define HT_BOARD_H

#include "settings.h"

#define setLed(STATE) digitalWrite(LED_PIN, INVERT_LED ^ STATE)

void blink(int count);

#endif //HT_BOARD_H
