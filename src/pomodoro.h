#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include "mode/timer.h"

static const uint8_t BUTTON_USE = 35;
static const uint8_t BUTTON_MODE = 0;

class Pomodoro
{

public:
    Pomodoro(TFT_eSPI &tft);
    ~Pomodoro() = default;
    void timerTick();
    void taskInputHandler();
    void taskDisplayHandler();

private:
    enum screen
    {
        TIMER,
        GAME_OF_LIFE,
        enumEnd
    };

    TFT_eSPI &tft;
    screen currentScreen;

    mode::Timer modeTimer;

    void useClicked();
    void useLongClicked();
    void modeClicked();
    void modeLongClicked();
};