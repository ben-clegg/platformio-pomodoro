#pragma once

#include <vector>
#include "mode.h"

namespace mode
{
    class GameOfLife : public Mode
    {
    public:
        GameOfLife(TFT_eSPI &tft);
        ~GameOfLife() = default;
        void update() override;
        void draw() override;
        void clickShort() override;
        void clickLong() override;
        void switchedTo() override;
    private:
        uint8_t neighbourCount(uint16_t x, uint16_t y);
        bool isAliveAndValid(uint16_t x, uint16_t y);
        static const uint8_t GRID_SCALE = 2;
        static const uint16_t GRID_WIDTH = DISPLAY_WIDTH / GRID_SCALE;
        static const uint16_t GRID_HEIGHT = DISPLAY_HEIGHT / GRID_SCALE;
        bool cells[GRID_HEIGHT][GRID_WIDTH];
        uint16_t iterations = 0;
        static const uint16_t MAX_ITERATIONS = 600;
        struct StateChange
        {
            uint16_t x;
            uint16_t y;
            bool newState;    
        };
    };
    
}