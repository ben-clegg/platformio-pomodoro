#include "gameOfLife.h"

namespace mode
{
    GameOfLife::GameOfLife(TFT_eSPI &tft) : Mode(tft)
    {

        for (uint16_t y = 0; y < GRID_HEIGHT; y++)
        {
            for (uint16_t x = 0; x < GRID_WIDTH; x++)
            {
                cells[y][x] = false;
            }
        }

        switchedTo();
    }

    void GameOfLife::update()
    {
        // Handle iteration limit
        if(iterations >= MAX_ITERATIONS) 
        {
            switchedTo();
            return;
        }
        iterations++;

        bool nextCells[GRID_HEIGHT][GRID_WIDTH];

        // Determine changes
        for (uint16_t y = 0; y < GRID_HEIGHT; y++)
        {
            for (uint16_t x = 0; x < GRID_WIDTH; x++)
            {
                uint8_t neighbours = neighbourCount(x, y);
                // Alive
                if (cells[y][x])
                {
                    // Continues living
                    if (neighbours == 2 || neighbours == 3)
                        nextCells[y][x] = true;
                    // Dies
                    else
                        nextCells[y][x] = false;
                }
                // Dead
                else
                {
                    // Born
                    if(neighbours == 3)
                        nextCells[y][x] = true;
                    // Remains dead
                    else
                        nextCells[y][x] = false;
                }
            }
        }

        // Replace current cells with nextCells
        for (uint16_t y = 0; y < GRID_HEIGHT; y++)
        {
            for (uint16_t x = 0; x < GRID_WIDTH; x++)
            {
                cells[y][x] = nextCells[y][x];
            }
        }
    }

    uint8_t GameOfLife::neighbourCount(uint16_t x, uint16_t y)
    {
        uint8_t n = 0;

        if (isAliveAndValid(x - 1, y - 1)) n++;
        if (isAliveAndValid(x - 1, y)) n++;
        if (isAliveAndValid(x - 1, y + 1)) n++;
        if (isAliveAndValid(x, y - 1)) n++;
        if (isAliveAndValid(x, y + 1)) n++;
        if (isAliveAndValid(x + 1, y - 1)) n++;
        if (isAliveAndValid(x + 1, y)) n++;
        if (isAliveAndValid(x + 1, y + 1)) n++;

        return n;
    }

    bool GameOfLife::isAliveAndValid(uint16_t x, uint16_t y)
    {
        // Allow wrapping; note underflows if < 0
        if(x >= GRID_WIDTH)
        {
            if (x > GRID_WIDTH)
                x = GRID_WIDTH - 1; // Underflow, wraps to right
            else 
                x = 0; // Overflow, wraps to left
        }

        if(y >= GRID_HEIGHT)
        {
            if (y > GRID_HEIGHT)
                y = GRID_HEIGHT - 1; // Underflow, wraps to bottom
            else 
                y = 0; // Overflow, wraps to top
        }
        
        return cells[y][x];
    }

    void GameOfLife::draw()
    {
        colour = TFT_GREENYELLOW;
        
        for (uint16_t y = 0; y < GRID_HEIGHT; y++)
        {
            for (uint16_t x = 0; x < GRID_WIDTH; x++)
            {
                if (cells[y][x])
                    tft.fillRect(x * GRID_SCALE, y * GRID_SCALE, GRID_SCALE, GRID_SCALE, colour);
                else
                    tft.fillRect(x * GRID_SCALE, y * GRID_SCALE, GRID_SCALE, GRID_SCALE, background);
            }
        }
        vTaskDelay(15);
    }

    void GameOfLife::clickShort()
    {
        // Reset 
        switchedTo();
        vTaskDelay(100);
    }

    void GameOfLife::clickLong()
    {
    }

    void GameOfLife::switchedTo()
    {
        // Populate cells
        for (uint16_t y = 0; y < GRID_HEIGHT; y++)
        {
            for (uint16_t x = 0; x < GRID_WIDTH; x++)
            {
                if (random(4) == 1)
                    cells[y][x] = true;
                else
                    cells[y][x] = false;
            }
        }
        iterations = 0;
    }
} // namespace mode