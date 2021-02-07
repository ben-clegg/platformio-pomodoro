#pragma once

#include "mode.h"

#define COLOUR_PRIMARY TFT_GREEN
#define COLOUR_SECONDARY TFT_BLACK

namespace mode
{
    class GameOfLife : public Mode
    {
    private:
        /* data */
    public:
        GameOfLife(TFT_eSPI &tft) : Mode(tft){};
        ~GameOfLife() = default;
        void update() override;
        void draw() override;
        void clickShort() override;
        void clickLong() override;
        void switchedTo() override;
    };
    
}