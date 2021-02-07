#include "timer.h"

namespace mode
{
    /*
    Timer::Timer(const String &timeTextToUse)
    {
        timeText = timeTextToUse;
    }
    */

    void Timer::update()
    {
    }

    void Timer::draw(TFT_eSPI &tft)
    {
        Serial.println("b");
        Serial.println(timeText);
    }

} // namespace mode
