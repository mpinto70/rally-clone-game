#pragma once

#include "game/Graphic.h"

#include <string>

namespace game {
namespace mck {

class GraphicMock : public Graphic {
public:
    ~GraphicMock() override;
    void printText(const std::string& text,
          GFONT font,
          unsigned x,
          unsigned y,
          COLOR foreground,
          COLOR background) override;
    void draw(const map::Map& map,
          size_t x,
          size_t y,
          size_t parts) override;

    void flip() override;
};
}
}
