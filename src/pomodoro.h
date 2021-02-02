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

class Pomodoro {
    
    public: 
        Pomodoro(TFT_eSPI &tft);
        ~Pomodoro() = default;
        void timerTick();
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


        TFT_eSPI &tft;

        boolean paused;
        timerStatus currentStatus;
        screen currentScreen;

        uint16_t timeCounter;
        String timeText;
        uint8_t completedPomos;

        
        void resetTimer(timerStatus newStatus);
        void updateColour();
        void taskInputHandler();
        void taskDisplayHandler();
        void useClicked();
        void useLongClicked();
        void modeClicked();
        String timerToString(uint16_t currentTimer);
        String intToPaddedString(uint8_t integer);
        void timerScreen();
        void gameOfLifeScreen();
};