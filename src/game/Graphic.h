#pragma once

#include "map/Map.h"

#include <string>

namespace game {

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

class Graphic {
public:
    virtual ~Graphic() = default;
    virtual void printText(const std::string& text,
          GFONT font,
          unsigned x,
          unsigned y,
          COLOR foreground,
          COLOR background) = 0;
    virtual void draw(const map::Map& map,
          size_t x,
          size_t y,
          size_t parts) = 0;
    virtual void flip() = 0;
};
}
