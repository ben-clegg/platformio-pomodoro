#pragma once

#include <TFT_eSPI.h>

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 135 // Actually 135

namespace mode
{
    class Mode
    {

    protected:
        TFT_eSPI &tft;
        uint16_t colour = TFT_GREEN;
        uint16_t background = TFT_BLACK;

    public:
        Mode(TFT_eSPI &tft) : tft(tft){};
        ~Mode() = default;
        virtual void update();
        virtual void draw();
        virtual void clickShort();
        virtual void clickLong();
        virtual void switchedTo();
    };

} // namespace mode