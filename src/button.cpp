#include "button.h"

Button::Button(uint8_t pinNum)
{
    pin = pinNum;
    pinMode(pin, INPUT_PULLUP);
}

void Button::update()
{
    int pinResult = digitalRead(pin);

    /* 
    Assumptions:
    - Unpressed state is stable (not bouncy).
    - Pressed state potentially unstable (bouncy).
    - The button will not be held before LONG_MAX milliseconds 
        have elapsed and released after.
        - See https://www.arduino.cc/reference/en/language/functions/time/millis/.
        - It may be possible to circumvent this limitation, 
            but it's very unlikely (only occurs every ~50 days uptime).
    
        */

    // Button "released" (may still be held if a bounce has occured)
    if ((pinResult == HIGH) && currentlyHeld)
    {
        if (!debouncing)
        {
            firstReleaseTime = millis();
            debouncing = true;
        }
        else if (millis() > firstReleaseTime + DEBOUNCE_TIME_MILLIS)
        {
            // Debounced; button definitely released
            debouncing = false;
            currentlyHeld = false;
            // Call relevant event function
            if (heldMillis >= LONG_PRESS_TIME_MILLIS)
                this->callEvent(LONG_PRESS);
            else if (heldMillis >= SHORT_PRESS_TIME_MILLIS)
                this->callEvent(SHORT_PRESS);
        }
    }
    // Button pressed
    else if (pinResult == LOW)
    {
        // Button pressed, bounce shouldn't occur
        debouncing = false;
        // First press
        if (!currentlyHeld)
        {
            currentlyHeld = true;
            firstPressTime = millis();
        }
    }

    // Update time held
    if (currentlyHeld)
    {
        heldMillis = millis() - firstPressTime;
    }
}

void Button::setEvent(event event, std::function<void()> response)
{
    events[event] = response;
}

void Button::callEvent(event event)
{
    if (events[event])
    {
        events[event]();
    }
}