#pragma once

#include "game/Graphic.h"
#include "gamelib/allegro/AllegroUtil.h"
#include "gamelib/allegro/bmp/ActionMapper.h"
#include "gamelib/allegro/bmp/TileMapper.h"

namespace gamelib {
namespace allegro {

class Graphic : public ::game::Graphic {
public:
    explicit Graphic(const std::string& common_path, unsigned width, unsigned height);
    ~Graphic() override;
    [[nodiscard]] unsigned width() const override { return width_; }
    [[nodiscard]] unsigned height() const override { return height_; }
    void printText(const std::string& text,
          game::GFONT gfont,
          unsigned x,
          unsigned y,
          game::COLOR foreground,
          game::COLOR background) override;
    void draw(const map::Map& map,
          size_t x,
          size_t y,
          size_t parts) override;

    void flip() override;

private:
    unsigned width_;
    unsigned height_;
    BITMAP_PTR buffer_;
    BITMAP_PTR bufferMap_;
    FONT_PTR fontSystem_;
    FONT_PTR fontMenu_;
    BITMAP_PTR fullImage_;
    bmp::TileMapper tileMapper_;
    bmp::ActionMapper actionMapper_;
};
}
}
