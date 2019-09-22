#include "Graphic.h"

#include "util/Exception.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <cmath>
#include <map>

namespace gamelib {
namespace allegro {

using bmp::TILE_SIZE;

namespace {
std::map<game::COLOR, ALLEGRO_COLOR> COLORS;
void initColor() {
    COLORS[game::COLOR::RED] = al_map_rgb(255, 0, 0);
    COLORS[game::COLOR::WINE] = al_map_rgb(64, 0, 0);
    COLORS[game::COLOR::GREEN] = al_map_rgb(0, 255, 0);
    COLORS[game::COLOR::DARKGREEN] = al_map_rgb(0, 64, 0);
    COLORS[game::COLOR::BLUE] = al_map_rgb(0, 0, 255);
    COLORS[game::COLOR::DARKBLUE] = al_map_rgb(0, 0, 64);
    COLORS[game::COLOR::WHITE] = al_map_rgb(255, 255, 255);
    COLORS[game::COLOR::GRAY] = al_map_rgb(128, 128, 128);
    COLORS[game::COLOR::DARKGRAY] = al_map_rgb(64, 64, 64);
    COLORS[game::COLOR::BLACK] = al_map_rgb(0, 0, 0);
}

const ALLEGRO_COLOR& translate(game::COLOR color) {
    return COLORS[color];
}
}

Graphic::Graphic(DISPLAY_PTR&& display,
      const std::string& commonPath,
      bmp::TileSource tileSource,
      bmp::CarSource carSource,
      bmp::CarSource enemySource)
      : display_(std::move(display)),
        fullImage_(bmp::SpriteReader::readFullImage(commonPath + "/Rally-general-sprites.png")),
        mapCanvas_(createBitmap(TILE_SIZE * 10, TILE_SIZE * 10)),
        fontSystem_(al_load_font((commonPath + "/font.ttf").c_str(), 18, 0)),
        fontMenu_(al_load_font((commonPath + "/font.ttf").c_str(), 24, 0)),
        tileMapper_(bmp::createTileMapper(*fullImage_, tileSource)),
        actionMapper_(bmp::createActionMapper(*fullImage_)),
        carMapper_(bmp::createCarMapper(*fullImage_, carSource)),
        enemyMapper_(bmp::createCarMapper(*fullImage_, enemySource)) {
    using util::Exception;

    if (display_ == nullptr) {
        throw Exception("Graphic::Graphic - Error initializing display", -1);
    }

    if (mapCanvas_ == nullptr) {
        throw Exception("Graphic::Graphic - Error initializing map canvas", -3);
    }

    if (fontMenu_ == nullptr) {
        throw Exception("Graphic::Graphic - Error initializing menu font [" + commonPath + "/font.ttf]", -4);
    }

    if (fontSystem_ == nullptr) {
        throw Exception("Graphic::Graphic - Error initializing system font [" + commonPath + "/font.ttf]", -5);
    }

    initColor();
}

Graphic::~Graphic() = default;

void Graphic::printText(const std::string& text,
      const game::GFONT gfont,
      const unsigned x,
      const unsigned y,
      const game::COLOR foreground,
      const game::COLOR /*background*/) {
    if (text.empty()) {
        return;
    }

    const auto font = gfont == game::GFONT::MENU_FONT ? fontMenu_ : fontSystem_;
    al_draw_textf(font, translate(foreground), x, y, 0, "%s", text.c_str());
}

void Graphic::draw(const map::Map&,
      const size_t /*x_cursor*/,
      const size_t /*y_cursor*/,
      const size_t /*parts*/) {
}

void Graphic::flip() {
    al_flip_display();
    al_clear_to_color(COLORS[game::COLOR::BLACK]);
}
}
}
