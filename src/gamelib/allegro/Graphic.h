#pragma once

#include "gamelib/Graphic.h"
#include "gamelib/allegro/AllegroUtil.h"
#include "gamelib/allegro/bmp/ActionMapper.h"
#include "gamelib/allegro/bmp/TileMapper.h"

#include <allegro.h>

namespace gamelib {
namespace allegro {

class Graphic : public ::gamelib::Graphic {
public:
    explicit Graphic(const std::string& common_path);
    ~Graphic() override;
    unsigned width() const override { return SCREEN_W; }
    unsigned height() const override { return SCREEN_H; }
    void printText(const std::string& text,
          GFONT gfont,
          unsigned x,
          unsigned y,
          COLOR foreground,
          COLOR background) override;
    void draw(const map::Map& map,
          size_t x,
          size_t y,
          size_t parts) override;

    void flip() override;

private:
    BITMAP_PTR buffer_;
    BITMAP_PTR bufferMap_;
    FONT_PTR fontSystem_;
    FONT_PTR fontMenu_;
    bmp::TileMapper tileMapper_;
    bmp::ActionMapper actionMapper_;
};
}
}
