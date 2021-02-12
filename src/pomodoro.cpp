#include "pomodoro.h"
#include "button.h"

Button buttonUse(BUTTON_USE);
Button buttonMode(BUTTON_MODE);

Pomodoro::Pomodoro(TFT_eSPI &tft) : tft(tft), modeTimer(tft)
{
    Serial.begin(9600);
    //currentScreen = TIMER;

    // Display
    tft.init();
    tft.setRotation(1);

    // Define modes
    modes.emplace_back(&modeTimer);
    modes.emplace_back(new mode::GameOfLife(tft));

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
        modes.at(currentMode)->update();
        modes.at(currentMode)->draw();
        // Needs some delay to prevent timing issues
        //delay(20);
    }
}

void Pomodoro::useClicked()
{
    modes.at(currentMode)->clickShort();
}

void Pomodoro::useLongClicked()
{
    modes.at(currentMode)->clickLong();
}

void Pomodoro::modeClicked()
{
    // Switch to next screen
    currentMode++;
    if (currentMode > modes.size() - 1)
        currentMode = 0;
    modes.at(currentMode)->switchedTo();
}

void Pomodoro::modeLongClicked()
{
    // Switch screen back to timer
    currentMode = 0;
}

void Pomodoro::timerTick()
{
    modeTimer.tick();
}
