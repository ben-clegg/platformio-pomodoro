#pragma once



#define BUTTON_USE  35
#define BUTTON_MODE 0

#define COLOUR_PRIMARY    TFT_GREEN
#define COLOUR_SECONDARY  TFT_BLACK
#define WAIT 200

#define FONT_CLOCK  7
#define TEXT_CLOCK_X  48
#define TEXT_CLOCK_Y  40

#define WORK_TIME   25
#define BREAK_TIME  5
#define SECONDS_PER_MIN 60

#include <Arduino.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include <Button2.h>

class Pomodoro {
    
    public: 
        Pomodoro(TFT_eSPI &tft);
        ~Pomodoro() = default;
        void loop();
    
    private: 
        enum timerStatus
        {
            POMO_RUNNING,
            BREAK,
            STOPPED
        };

        enum screen
        {
            TIMER,
            GAME_OF_LIFE
        };

        hw_timer_t * timer;

        TFT_eSPI &tft;

        boolean paused;
        timerStatus currentStatus;
        screen currentScreen;

        uint16_t timeCounter;
        String timeText;
        uint8_t completedPomos;

        Button2 buttonUse;
        Button2 buttonMode;

        
        void IRAM_ATTR onTimer();
        void resetTimer(timerStatus newStatus);
        void updateColour();
        void taskInputHandler();
        void taskDisplayHandler();
        void useClicked(Button2& btn);
        void useLongClicked(Button2& btn);
        void modeClicked(Button2& btn);
        String timerToString(uint16_t currentTimer);
        String intToPaddedString(uint8_t integer);
        void timerScreen();
        void gameOfLifeScreen();
};