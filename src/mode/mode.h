#pragma once

#include <TFT_eSPI.h>

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 135 // Actually 135

namespace mode
{
    class Mode
    {
    private:
        uint16_t targetFrametime = 500; // 50 ms = 20 FPS default
        unsigned long lastFrametime = 0;
    protected:
        TFT_eSPI &tft;
        uint16_t colour = TFT_GREEN;
        uint16_t background = TFT_BLACK;
        void setTargetFramerate(uint8_t targetFramerate);

    public:
        Mode(TFT_eSPI &tft) : tft(tft){};
        ~Mode() = default;
        virtual void update();
        virtual void draw();
        virtual void clickShort();
        virtual void clickLong();
        virtual void switchedTo();
        void frameDelay();
    };

} // namespace mode