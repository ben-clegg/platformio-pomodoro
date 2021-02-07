#include "pomodoro.h"
#include "button.h"

Button buttonUse(BUTTON_USE);
Button buttonMode(BUTTON_MODE);

Pomodoro::Pomodoro(TFT_eSPI &tft) : tft(tft), modeTimer(tft)
{
    Serial.begin(9600);
    currentScreen = TIMER;

    // Display
    tft.init();
    tft.setRotation(1);

    // Buttons
    buttonUse.setEvent(Button::event::SHORT_PRESS, std::bind(&Pomodoro::useClicked, this));
    buttonUse.setEvent(Button::event::LONG_PRESS, std::bind(&Pomodoro::useLongClicked, this));
    buttonMode.setEvent(Button::event::SHORT_PRESS, std::bind(&Pomodoro::modeClicked, this));
    buttonMode.setEvent(Button::event::LONG_PRESS, std::bind(&Pomodoro::modeLongClicked, this));

    Serial.println("pomo created");
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
        modeTimer.update();
        modeTimer.draw();

        // Delay to reduce screen redraws
        delay(200);
    }
}

void Pomodoro::useClicked()
{
    switch (currentScreen)
    {
    case TIMER:
        modeTimer.clickShort();
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
        modeTimer.clickLong();
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
    currentScreen = (screen)nextScreenNumber;
}

void Pomodoro::modeLongClicked()
{
    // Switch screen back to timer
    currentScreen = TIMER;
}

void Pomodoro::timerTick()
{
    modeTimer.tick();
}
