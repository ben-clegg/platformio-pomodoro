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

        bool currentlyHeld = false;
        bool debouncing = false;
        unsigned long firstPressTime = 0;
        unsigned long firstReleaseTime = 0;
        unsigned long heldMillis = 0;
        static const uint8_t DEBOUNCE_TIME_MILLIS = 10;
        static const uint8_t SHORT_PRESS_TIME_MILLIS = 20;
        static const uint8_t LONG_PRESS_TIME_MILLIS = 1000;


        void callEvent(event event);
};