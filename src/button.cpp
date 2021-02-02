#include "button.h"

Button::Button(uint8_t pin)
{
    pin = pin;
    pinMode(pin, INPUT_PULLUP);
}

void Button::update()
{
    // TODO handle logic for detecting button presses
    // TODO debounce
}

void Button::setEvent(event event, Button::vFunctionCall response)
{
    events[event] = response;
}

void Button::callEvent(event event)
{
    if(events[event])
    {
        events[event]();
    }
}