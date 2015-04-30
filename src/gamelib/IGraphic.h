
#pragma once

#include "map/CMap.h"

#include <string>

namespace gamelib {

enum class GFONT : unsigned char {
    SYSTEM_FONT = 1,
    MENU_FONT,
};

enum class COLOR : unsigned {
    RED,
    WINE,
    GREEN,
    DARKGREEN,
    BLUE,
    DARKBLUE,
    WHITE,
    GRAY,
    DARKGRAY,
    BLACK
};

class IGraphic {
    public:
        virtual ~IGraphic() = 0;
        virtual unsigned width() const = 0;
        virtual unsigned height() const = 0;
        virtual void printText(const std::string & text,
                               GFONT font,
                               unsigned x,
                               unsigned y,
                               COLOR foreground,
                               COLOR background) = 0;
        virtual void draw(const map::CMap & map,
                          size_t x,
                          size_t y,
                          size_t parts) = 0;
        virtual void flip() = 0;
};

}

