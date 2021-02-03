#pragma once


#include <Arduino.h>
#include <map>

class Button 
{
    public:
    
        typedef void (* vFunctionCall)(void);
        
        enum event
        {
            SHORT_PRESS,
            LONG_PRESS
        };

        Button(uint8_t pinNum);
        ~Button() = default;
        void update();
        void setEvent(event event, vFunctionCall response);

    private:
        uint8_t pin;
        std::map<event, vFunctionCall> events;

        void callEvent(event event);
};