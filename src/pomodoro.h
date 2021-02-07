#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include <vector>
#include <memory>
#include "mode/mode.h"
#include "mode/timer.h"
#include "mode/gameOfLife.h"

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
/*
    enum screen
    {
        TIMER,
        GAME_OF_LIFE,
        enumEnd
    };
    */

    std::vector<std::unique_ptr<mode::Mode>> modes; 

    TFT_eSPI &tft;
    uint8_t currentMode = 0;

    mode::Timer modeTimer;

    void useClicked();
    void useLongClicked();
    void modeClicked();
    void modeLongClicked();
    mode::Mode getCurrentMode();
};