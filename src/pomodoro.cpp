#include "pomodoro.h"

Pomodoro::Pomodoro(TFT_eSPI &tft) : tft(tft) 
{
    paused = false;
    currentStatus = STOPPED;
    currentScreen = TIMER;
    timeCounter = 0;
    timeText = "--:--";
    completedPomos = 0;

    buttonUse = Button2(BUTTON_USE);
    buttonMode = Button2(BUTTON_MODE);


    delay(50);
    Serial.begin(9600);
    Serial.println("start");
    // Display
    tft.init();
    tft.setRotation(1);

    // Buttons 
    buttonUse.setClickHandler((*Button2::CallbackFunction)(){&Pomodoro::useClicked});
    //buttonUse.setLongClickHandler(useLongClicked);
    //buttonMode.setClickHandler(modeClicked);

    // Init timer
    timer = timerBegin(0, 80, true);

    // Attach onTimer function to our timer.
    //timerAttachInterrupt(timer, &onTimer, true);

    // Set alarm to call onTimer function every second (value in microseconds).
    // Repeat the alarm (third parameter)
    timerAlarmWrite(timer, 1000000, true);

    // Start an alarm
    timerAlarmEnable(timer);

    // Setup timer
    resetTimer(Pomodoro::timerStatus::POMO_RUNNING);
    paused = true;
    updateColour();
}

void IRAM_ATTR Pomodoro::onTimer() {
  // Decrement timer
  if((currentStatus != STOPPED) && (!paused)) {
    timeCounter--;
    timeText = timerToString(timeCounter);

    // Switch timer status
    if (timeCounter <= 0) {
      switch(currentStatus) {
        case POMO_RUNNING:
          resetTimer(BREAK);
          //currentStatus = BREAK;
          //timeCounter = BREAK_TIME * SECONDS_PER_MIN;
          completedPomos++;
          break;
        case BREAK: 
          resetTimer(POMO_RUNNING);
          //currentStatus = POMO_RUNNING;
          //timeCounter = WORK_TIME * SECONDS_PER_MIN;
          break;
      }
      paused = true;
    }
  }
}

void Pomodoro::loop() 
{

}

void Pomodoro::resetTimer(timerStatus newStatus) {
  switch(newStatus) {
    case POMO_RUNNING:
      timeCounter = WORK_TIME * SECONDS_PER_MIN;
      break;
    case BREAK:
      timeCounter = BREAK_TIME * SECONDS_PER_MIN;
      break;
  }
  timeText = timerToString(timeCounter);
  currentStatus = newStatus;
  paused = false;
}

void Pomodoro::updateColour() {
  if(paused) {
    tft.fillScreen(COLOUR_PRIMARY);
    tft.setTextColor(COLOUR_SECONDARY, COLOUR_PRIMARY);
  }
  else {
    tft.fillScreen(COLOUR_SECONDARY);
    tft.setTextColor(COLOUR_PRIMARY, COLOUR_SECONDARY);
  }
}

void Pomodoro::taskInputHandler() {
  buttonUse.loop();
  buttonMode.loop();
}

void Pomodoro::taskDisplayHandler() {
  timerScreen();
}

void Pomodoro::useClicked(Button2& btn) {
    Serial.println("A clicked");
    switch(currentScreen) {
    case TIMER:
        if(currentStatus == STOPPED) {
            resetTimer(POMO_RUNNING);
        }
        else {
        paused = !paused;
        updateColour();
        }
        break;
    case GAME_OF_LIFE:
        break;
  }
}

void Pomodoro::useLongClicked(Button2& btn) {
    Serial.println("A longclicked");

    switch(currentScreen) {
    case TIMER:
        resetTimer(POMO_RUNNING);
        currentStatus = STOPPED;
        break;
    }
}

void Pomodoro::modeClicked(Button2& btn) {
    Serial.println("B clicked");
}

String Pomodoro::timerToString(uint16_t currentTimer) {
  // mm:ss
  uint8_t secs = currentTimer % SECONDS_PER_MIN;
  uint8_t mins = (currentTimer - secs) / SECONDS_PER_MIN;

  String timeStr = intToPaddedString(mins);
  timeStr.concat(":");
  timeStr.concat(intToPaddedString(secs));

  return timeStr;
}

String Pomodoro::intToPaddedString(uint8_t integer) {
  if (integer >= 10) {
    return String(integer);
  }
  String str = "0";
  str.concat(String(integer));
  return str;
}

void Pomodoro::timerScreen() {
  tft.setTextSize(1);
  //delay(WAIT); // each part of loop() must be separate thread before wait can be used again
  tft.drawString(timeText, TEXT_CLOCK_X, TEXT_CLOCK_Y, FONT_CLOCK);
}

void Pomodoro::gameOfLifeScreen() {
  
}