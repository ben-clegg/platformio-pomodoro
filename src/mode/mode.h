#pragma once

#include <TFT_eSPI.h>

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
    };

} // namespace mode