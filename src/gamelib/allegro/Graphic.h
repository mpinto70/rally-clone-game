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
    explicit Graphic(const std::string& common_path,
            unsigned width,
            unsigned height,
            bmp::TileSource tileSource = bmp::TileSource::GREEN,
            bmp::CarSource carSource = bmp::CarSource::PLAYER_1,
            bmp::CarSource enemySource = bmp::CarSource::ENEMY_1);
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

    DISPLAY_PTR& display() {
        return display_;
    }

    EVENT_QUEUE_PTR& eventQueue() {
        return eventQueue_;
    }

    BITMAP_PTR& mapCanvas() {
        return mapCanvas_;
    }

    [[nodiscard]] const BITMAP_PTR& fullImage() const {
        return fullImage_;
    }

    FONT_PTR& fontSystem() {
        return fontSystem_;
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
    unsigned width_;
    unsigned height_;
    DISPLAY_PTR display_;
    EVENT_QUEUE_PTR eventQueue_;
    BITMAP_PTR mapCanvas_;
    FONT_PTR fontSystem_;
    FONT_PTR fontMenu_;
    BITMAP_PTR fullImage_;
    bmp::TileMapper tileMapper_;
    bmp::ActionMapper actionMapper_;
    bmp::CarMapper carMapper_;
    bmp::CarMapper enemyMapper_;
};
}
}
