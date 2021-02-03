#include "button.h"

Button::Button(uint8_t pinNum)
{
    pin = pinNum;
    pinMode(pin, INPUT_PULLUP);
}

void Button::update()
{
    // TODO handle logic for detecting button presses
    if(digitalRead(pin) == LOW)
    {
        callEvent(event::SHORT_PRESS);
    }
    else 
    {

    }
    // TODO debounce
}

void Button::setEvent(event event, std::function<void()>  response)
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