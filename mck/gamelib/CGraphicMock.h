
#pragma once

#include <string>

#include "gamelib/IGraphic.h"

namespace gamelib {
namespace mck {

class CGraphicMock : public IGraphic {
    public:
        ~CGraphicMock() override;
        unsigned width() const override { return 0; }
        unsigned height() const override { return 0; }
        void printText(const std::string & text,
                       GFONT font,
                       unsigned x,
                       unsigned y,
                       COLOR foreground,
                       COLOR background) override;
        void draw(const map::CMap & map,
                  size_t x,
                  size_t y,
                  size_t parts) override;

        void flip() override;
};

}
}
