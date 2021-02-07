#include "timer.h"

namespace mode
{

    Timer::Timer(TFT_eSPI &tft) : Mode(tft)
    {
        paused = false;
        timeCounter = 0;
        completedPomos = 0;
        currentStatus = IN_POMODORO;

        // Setup timer
        resetTimer(IN_POMODORO);
        updateColour();
    }

    void Timer::update()
    {
    }

    void Timer::draw()
    {
        updateColour();
        tft.setTextSize(1);
        tft.drawString(timeText, TEXT_CLOCK_X, TEXT_CLOCK_Y, FONT_CLOCK);
    }

    void Timer::resetTimer(timerStatus newStatus)
    {
        switch (newStatus)
        {
        case IN_POMODORO:
            timeCounter = WORK_TIME * SECONDS_PER_MIN;
            break;
        case BREAK:
            timeCounter = BREAK_TIME * SECONDS_PER_MIN;
            break;
        }
        timeText = timerToString(timeCounter);
        currentStatus = newStatus;
        paused = true;
        //updateColour();
    }

    void Timer::updateColour()
    {
        // Skip if no state change
        if (paused == pausedLastTick)
        {
            return;
        }

        // State changed
        if (paused)
        {
            tft.fillScreen(COLOUR_PRIMARY);
            tft.setTextColor(COLOUR_SECONDARY, COLOUR_PRIMARY);
        }
        else
        {
            tft.fillScreen(COLOUR_SECONDARY);
            tft.setTextColor(COLOUR_PRIMARY, COLOUR_SECONDARY);
        }
        pausedLastTick = paused;
    }

    void Timer::clickShort()
    {
        paused = !paused;
    }

    void Timer::clickLong()
    {
        resetTimer(mode::Timer::timerStatus::IN_POMODORO);
    }

    String Timer::timerToString(uint16_t currentTimer)
    {
        // mm:ss
        uint8_t secs = currentTimer % SECONDS_PER_MIN;
        uint8_t mins = (currentTimer - secs) / SECONDS_PER_MIN;

        String timeStr = intToPaddedString(mins);
        timeStr.concat(":");
        timeStr.concat(intToPaddedString(secs));

        return timeStr;
    }

    String Timer::intToPaddedString(uint8_t integer)
    {
        if (integer >= 10)
        {
            return String(integer);
        }
        String str = "0";
        str.concat(String(integer));
        return str;
    }

    void Timer::switchedTo()
    {
        pausedLastTick = !paused;
    }

    void Timer::tick()
    {
        // Decrement timer
        if (!paused)
        {
            timeCounter--;
            timeText = timerToString(timeCounter);

            // Switch timer status
            if (timeCounter <= 0)
            {
                switch (currentStatus)
                {
                case IN_POMODORO:
                    resetTimer(BREAK);
                    completedPomos++;
                    break;
                case BREAK:
                    resetTimer(IN_POMODORO);
                    break;
                default:
                    break;
                }
            }
        }
    }

} // namespace mode
