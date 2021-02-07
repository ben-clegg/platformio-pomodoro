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
        bool nextCells[GRID_HEIGHT][GRID_WIDTH];

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

        for (int8_t yOff = -1; yOff <= 1; yOff++)
        {
            for (int8_t xOff = -1; xOff <= 1; xOff++)
            {
                if ((yOff != 0) || (xOff != 0))
                {
                    if (isAliveAndValid(x + xOff, y + yOff))
                        n++;
                }
            }
        }

        return n;
    }

    bool GameOfLife::isAliveAndValid(uint16_t x, uint16_t y)
    {
        // Only need to check >= because ints are unsigned (underflow if < 0)
        if ((x >= GRID_WIDTH) || (y >= GRID_HEIGHT))
            return false;
        return cells[y][x];
    }

    void GameOfLife::draw()
    {
        for (uint16_t y = 0; y < GRID_HEIGHT; y++)
        {
            for (uint16_t x = 0; x < GRID_WIDTH; x++)
            {
                uint16_t colour = COLOUR_SECONDARY;
                if (cells[y][x])
                    colour = COLOUR_PRIMARY;
                tft.fillRect(x * GRID_SCALE, y * GRID_SCALE, GRID_SCALE, GRID_SCALE, colour);
            }
        }
        //delay(100);
    }

    void GameOfLife::clickShort()
    {
        // Reset 
        switchedTo();
        delay(100);
    }

    void GameOfLife::clickLong()
    {
    }

    void GameOfLife::switchedTo()
    {
        // Clear screen
        tft.fillScreen(COLOUR_SECONDARY);

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
    }
} // namespace mode