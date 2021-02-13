#include "mode.h"

namespace mode
{
    void Mode::frameDelay()
    {
        unsigned long currentTime = millis();
        uint16_t timeDelta = currentTime - lastFrametime;
        
        if (timeDelta < targetFrametime)
        {
            vTaskDelay((targetFrametime - timeDelta) / portTICK_PERIOD_MS);
        }

        lastFrametime = currentTime;
    }
    
    void Mode::setTargetFramerate(uint8_t targetFramerate)
    {
        targetFrametime = 1000 / targetFramerate;
    }
}