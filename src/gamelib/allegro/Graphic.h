#pragma once

#include "game/Graphic.h"
#include "gamelib/allegro/AllegroUtil.h"
#include "gamelib/allegro/bmp/ActionMapper.h"
#include "gamelib/allegro/bmp/CarMapper.h"
#include "gamelib/allegro/bmp/TileMapper.h"

namespace gamelib {
namespace allegro {
class Graphic : public ::game::Graphic {
public:
    Graphic(DISPLAY_PTR&& display,
          const std::string& commonPath,
          bmp::TileSource tileSource,
          bmp::CarSource carSource,
          bmp::CarSource enemySource);
    ~Graphic() override;

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

    ALLEGRO_DISPLAY& display() {
        return *display_;
    }

    ALLEGRO_BITMAP& mapCanvas() {
        return *mapCanvas_;
    }

    ALLEGRO_BITMAP& fullImage() {
        return *fullImage_;
    }

    [[nodiscard]] const ALLEGRO_FONT& fontSystem() const {
        return *fontSystem_;
    }

    [[nodiscard]] const bmp::TileMapper& tileMapper() const {
        return tileMapper_;
    }

    [[nodiscard]] const bmp::ActionMapper& actionMapper() const {
        return actionMapper_;
    }

    [[nodiscard]] const bmp::CarMapper& carMapper() const {
        return carMapper_;
    }

    [[nodiscard]] const bmp::CarMapper& enemyMapper() const {
        return enemyMapper_;
    }

private:
    DISPLAY_PTR display_;
    ALLEGRO_BITMAP* fullImage_;
    BITMAP_PTR mapCanvas_;
    ALLEGRO_FONT* fontSystem_;
    ALLEGRO_FONT* fontMenu_;
    bmp::TileMapper tileMapper_;
    bmp::ActionMapper actionMapper_;
    bmp::CarMapper carMapper_;
    bmp::CarMapper enemyMapper_;
};
}
}
