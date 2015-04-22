/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de gfx.
*/

#pragma once

#include "gamelib/IGraphic.h"
#include "gamelib/allegro/AllegroUtil.h"
#include "gamelib/allegro/bmp/CTileMapper.h"
#include "gamelib/allegro/bmp/CActionMapper.h"

#include <allegro.h>

namespace gamelib {
namespace allegro {

class CGraphic : public IGraphic {
    public:
        CGraphic(const std::string & common_path);
        ~CGraphic() override;
        unsigned width() const override { return SCREEN_W; }
        unsigned height() const override { return SCREEN_H; }
        void printText(const std::string & text,
                       GFONT gfont,
                       unsigned x,
                       unsigned y,
                       COLOR foreground,
                       COLOR background) override;
        void draw(const map::CMap & map,
                  size_t x,
                  size_t y) override;

        void flip() override;
    private:
        BITMAP_PTR buffer_;
        FONT_PTR fontSystem_;
        FONT_PTR fontMenu_;
        bmp::CTileMapper tileMapper_;
        bmp::CActionMapper actionMapper_;
};

}
}

