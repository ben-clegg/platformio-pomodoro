#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#include "main.h"

TFT_eSPI tft = TFT_eSPI();
Pomodoro pomo(tft);

void IRAM_ATTR onTimer() 
{
  pomo.timerTick();
}

void setup()
{
  Serial.println("Main entered");

  // Init hardware timer
  timer = timerBegin(0, 80, true);
  // Attach onTimer function to our timer.
  timerAttachInterrupt(timer, &onTimer, true);
  // Set alarm to call onTimer function every second (value in microseconds).
  // Repeat the alarm (third parameter)
  timerAlarmWrite(timer, 1000000, true);
  // Start an alarm
  timerAlarmEnable(timer);
}

void loop()
{
  pomo.loop();
}