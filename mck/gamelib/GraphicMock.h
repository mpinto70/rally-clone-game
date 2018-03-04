#pragma once

#include "gamelib/Graphic.h"

#include <string>


namespace gamelib {
namespace mck {

class GraphicMock : public Graphic {
    public:
        ~GraphicMock() override;
        unsigned width() const override { return 0; }
        unsigned height() const override { return 0; }
        void printText(const std::string & text,
                       GFONT font,
                       unsigned x,
                       unsigned y,
                       COLOR foreground,
                       COLOR background) override;
        void draw(const map::Map & map,
                  size_t x,
                  size_t y,
                  size_t parts) override;

        void flip() override;
};

}
}
