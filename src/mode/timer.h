#pragma once

#include <Arduino.h>
#include "mode.h"

#define WORK_TIME 25
#define BREAK_TIME 5
#define SECONDS_PER_MIN 60
#define WAIT 200

#define FONT_CLOCK 7
#define TEXT_CLOCK_X 48
#define TEXT_CLOCK_Y 40

namespace mode
{

    class Timer : public Mode
    {
    public:
        enum timerStatus
        {
            IN_POMODORO,
            BREAK
        };

    private:
        uint16_t timeCounter;
        uint8_t completedPomos;
        String timeText = "--:--";

        timerStatus currentStatus;
        boolean paused = true;
        boolean pausedLastTick = false;

        void resetTimer(timerStatus newStatus);
        void updateColour();
        String timerToString(uint16_t currentTimer);
        String intToPaddedString(uint8_t integer);

    public:
        Timer(TFT_eSPI &tft);
        ~Timer() = default;
        void update() override;
        void draw() override;
        void clickShort() override;
        void clickLong() override;
        void switchedTo() override;
        void tick();
    };

} // namespace mode