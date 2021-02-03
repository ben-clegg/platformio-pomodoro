#pragma once


#include <Arduino.h>
#include <map>
#include <functional>

class Button 
{
    public:
        
        enum event
        {
            SHORT_PRESS,
            LONG_PRESS
        };

        Button(uint8_t pinNum);
        ~Button() = default;
        void update();
        void setEvent(event event, std::function<void()> response);

    private:
        uint8_t pin;
        std::map<event, std::function<void()>> events;

        void callEvent(event event);
};