#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#include "main.h"

TFT_eSPI tft = TFT_eSPI();
Pomodoro pomo(tft);

void setup()
{

}

void loop()
{
  pomo.loop();
}