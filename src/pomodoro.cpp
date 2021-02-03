#include "pomodoro.h"
#include "button.h"

Button buttonUse(BUTTON_USE);
Button buttonMode(BUTTON_MODE);

Pomodoro::Pomodoro(TFT_eSPI &tft) : tft(tft) 
{
  delay(500);
  Serial.println("pomo created");
  
  paused = false;
  currentStatus = STOPPED;
  currentScreen = TIMER;
  timeCounter = 0;
  timeText = "--:--";
  completedPomos = 0;

  delay(50);
  Serial.begin(9600);
  Serial.println("start");
  // Display
  tft.init();
  tft.setRotation(1);

  // Buttons 
  buttonUse.setEvent(Button::event::SHORT_PRESS, std::bind(&Pomodoro::useClicked, this));
  buttonMode.setEvent(Button::event::SHORT_PRESS, std::bind(&Pomodoro::modeClicked, this));

  // Setup timer
  resetTimer(POMO_RUNNING);
  paused = true;
  updateColour();

  Serial.println(currentStatus);
  Serial.println(currentScreen);
}

void Pomodoro::timerTick() {
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
        default:
          break;
      }
      paused = true;
    }
  }
}

void Pomodoro::loop() 
{
  taskDisplayHandler();
  taskInputHandler();
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

void Pomodoro::taskInputHandler() 
{
  buttonUse.update();
  buttonMode.update();
}

void Pomodoro::taskDisplayHandler() {
  timerScreen();
}

void Pomodoro::useClicked() {
  switch(currentScreen) {
    case TIMER:
      if(currentStatus == STOPPED) {
        Serial.println("Resume");
        resetTimer(POMO_RUNNING);
      }
      else {
        Serial.println("Pause toggle");
        paused = !paused;
        updateColour();
      }
      break;
    case GAME_OF_LIFE:
      break;
    default:
      break;
  }
}

void Pomodoro::useLongClicked() {
    Serial.println("A longclicked");

    switch(currentScreen) {
    case TIMER:
        resetTimer(POMO_RUNNING);
        currentStatus = STOPPED;
        break;
    default:
      break;
    }
}

void Pomodoro::modeClicked() {
    Serial.println("Mode clicked");
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