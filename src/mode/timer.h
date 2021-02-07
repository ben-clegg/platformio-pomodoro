#pragma once

#include <Arduino.h>
#include "mode.h"

namespace mode
{

    class Timer : public Mode
    {
    private:
        const String &timeText;

    public:
        Timer(const String &timeTextToUse) : timeText(timeTextToUse) {}
        ~Timer() = default;
        void update() override;
        void draw(TFT_eSPI &tft) override;
    };

} // namespace mode