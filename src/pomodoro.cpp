#include "pomodoro.h"
#include "button.h"

Button buttonUse(BUTTON_USE);
Button buttonMode(BUTTON_MODE);

Pomodoro::Pomodoro(TFT_eSPI &tft) : tft(tft)
{
    paused = false;
    currentStatus = IN_POMODORO;
    currentScreen = TIMER;
    timeCounter = 0;
    timeText = "--:--";
    completedPomos = 0;

    // Display
    tft.init();
    tft.setRotation(1);

    // Buttons
    buttonUse.setEvent(Button::event::SHORT_PRESS, std::bind(&Pomodoro::useClicked, this));
    buttonUse.setEvent(Button::event::LONG_PRESS, std::bind(&Pomodoro::useLongClicked, this));
    buttonMode.setEvent(Button::event::SHORT_PRESS, std::bind(&Pomodoro::modeClicked, this));
    buttonMode.setEvent(Button::event::LONG_PRESS, std::bind(&Pomodoro::modeLongClicked, this));

    // Setup timer
    resetTimer(IN_POMODORO);
    updateColour();

    Serial.println("pomo created");
}

void Pomodoro::timerTick()
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

void Pomodoro::resetTimer(timerStatus newStatus)
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

void Pomodoro::updateColour()
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

void Pomodoro::taskInputHandler()
{
    for (;;)
    {
        buttonUse.update();
        buttonMode.update();
    }
}

void Pomodoro::taskDisplayHandler()
{
    for (;;)
    {
        updateColour();
        timerScreen();
        // Delay to reduce screen redraws
        delay(200);
    }
}

void Pomodoro::useClicked()
{
    switch (currentScreen)
    {
    case TIMER:
        paused = !paused;
        //updateColour();
        break;
    case GAME_OF_LIFE:
        break;
    default:
        break;
    }
}

void Pomodoro::useLongClicked()
{
    switch (currentScreen)
    {
    case TIMER:
        resetTimer(IN_POMODORO);
        break;
    default:
        break;
    }
}

void Pomodoro::modeClicked()
{
    // Switch to next screen
    int nextScreenNumber = currentScreen + 1;
    if (nextScreenNumber >= enumEnd)
        nextScreenNumber = 0;
    currentScreen = (screen) nextScreenNumber;
}

void Pomodoro::modeLongClicked()
{
    // Switch screen back to timer
    currentScreen = TIMER;
}

String Pomodoro::timerToString(uint16_t currentTimer)
{
    // mm:ss
    uint8_t secs = currentTimer % SECONDS_PER_MIN;
    uint8_t mins = (currentTimer - secs) / SECONDS_PER_MIN;

    String timeStr = intToPaddedString(mins);
    timeStr.concat(":");
    timeStr.concat(intToPaddedString(secs));

    return timeStr;
}

String Pomodoro::intToPaddedString(uint8_t integer)
{
    if (integer >= 10)
    {
        return String(integer);
    }
    String str = "0";
    str.concat(String(integer));
    return str;
}

void Pomodoro::timerScreen()
{
    tft.setTextSize(1);
    tft.drawString(timeText, TEXT_CLOCK_X, TEXT_CLOCK_Y, FONT_CLOCK);
}

void Pomodoro::gameOfLifeScreen()
{
}