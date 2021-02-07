#pragma once

#include <TFT_eSPI.h>

namespace mode
{
    class Mode
    {

    private:
    public:
        Mode() {};
        ~Mode() = default;
        virtual void update();
        virtual void draw(TFT_eSPI &tft);
    };

} // namespace mode