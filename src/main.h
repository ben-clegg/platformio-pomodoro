#pragma once

#include <TFT_eSPI.h>
#include "pomodoro.h"

hw_timer_t *timer;

void IRAM_ATTR onTimer();
void setup();
void loop();