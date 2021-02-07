#pragma once

#include <TFT_eSPI.h>

#define COLOUR_PRIMARY TFT_GREEN
#define COLOUR_SECONDARY TFT_BLACK

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 135 // Actually 135

namespace mode
{
    class Mode
    {

    protected:
        TFT_eSPI &tft;

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