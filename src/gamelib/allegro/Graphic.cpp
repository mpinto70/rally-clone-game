#include "Graphic.h"

#include "util/Exception.h"

#include <allegro5/allegro_primitives.h>

#include <cmath>
#include <map>

namespace gamelib {
namespace allegro {

static constexpr unsigned TILE_SIZE = 32;    ///< tile size in pixels
static constexpr unsigned SIDE_BAR_W = 200;  ///< width of the side bar
static constexpr unsigned BOTTOM_BAR_H = 50; ///< width of the side bar

static std::map<game::COLOR, ALLEGRO_COLOR> COLORS;
static void initColor() {
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

static const ALLEGRO_COLOR& translate(game::COLOR color) {
    return COLORS[color];
}

Graphic::Graphic(const std::string& common_path, unsigned width, unsigned height)
      : width_(width),
        height_(height),
        buffer_(nullptr, al_destroy_bitmap),
        bufferMap_(nullptr, al_destroy_bitmap),
        fontSystem_(nullptr, al_destroy_font),
        fontMenu_(nullptr, al_destroy_font),
        fullImage_(bmp::SpriteReader::readFullImage(common_path + "/Rally-general-sprites.png")),
        tileMapper_(bmp::createTileMapper(fullImage_, bmp::TileSource::GREEN)),
        actionMapper_(bmp::createActionMapper(fullImage_)) {
    using util::Exception;
    // creates the buffer of the entire screen
    buffer_.reset(al_create_bitmap(width, height));
    if (buffer_.get() == nullptr) {
        throw Exception("Graphic::Graphic - Error initializing main screen buffer", -1);
    }

    // creates the buffer for the map.
    bufferMap_.reset(al_create_bitmap(width - SIDE_BAR_W, width - BOTTOM_BAR_H));
    if (bufferMap_.get() == nullptr) {
        throw Exception("Graphic::Graphic - Error initializing map buffer", -1);
    }

    fontMenu_.reset(al_load_font((common_path + "/Menu_font.pcx").c_str(), 18, 0));
    if (fontMenu_.get() == nullptr) {
        throw Exception("Graphic::Graphic - Error initializing menu font [" + common_path + "/Menu_font.pcx]", -2);
    }

    fontSystem_.reset(al_load_font((common_path + "/Menu_font.pcx").c_str(), 18, 0));
    if (fontSystem_.get() == nullptr) {
        throw Exception("Graphic::Graphic - Error initializing system font [" + common_path + "/Menu_font.pcx]", -3);
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
    if (x > width() || y > height()) {
        return;
    }

    if (text.empty()) {
        return;
    }

    const auto font = gfont == game::GFONT::MENU_FONT ? fontMenu_.get() : fontSystem_.get();
    al_draw_textf(font, translate(foreground), x, y, 0, "%s", text.c_str());
}

template <typename MAPPER>
static void mapper_draw(const MAPPER& mapper,
      const typename MAPPER::enum_type type,
      const int x,
      const int y) {
    const auto sub_bmp = mapper[type];
    al_draw_bitmap(sub_bmp, x, y, 0);
}

static void tile_draw(const gamelib::allegro::bmp::TileMapper& mapper,
      const map::TileType type,
      const int x,
      const int y) {
    mapper_draw(mapper, type, x, y);
}

static void action_draw(const gamelib::allegro::bmp::ActionMapper& mapper,
      const map::Action action,
      const int x,
      const int y) {
    mapper_draw(mapper, action, x, y);
}

static double calculateMin(double x,
      double windowW,
      double maxX) {
    const double res = x - windowW / 2.0;
    if (res < 0) {
        return 0;
    }
    if (res + windowW > maxX) {
        return maxX - windowW;
    }
    return res;
}

void Graphic::draw(const map::Map& map,
      const size_t x_cursor,
      const size_t y_cursor,
      const size_t parts) {
    al_draw_filled_rectangle(0, 0, width_, height_, COLORS[game::COLOR::WINE]);
    al_draw_rectangle(0, 0, width_ - 1, height_ - 1, COLORS[game::COLOR::WHITE], 2);

    // ratio between the tile size on screen and the number of logical divisions inside tile
    const double ratio_S_T = (double) TILE_SIZE / parts;

    // converting cursor logical coordinate to screen coordinate (if screen was full size)
    const double x = x_cursor * ratio_S_T;
    const double y = y_cursor * ratio_S_T;

    // calculation window that will be shown
    const double window_x0 = calculateMin(x, width_, map.width() * TILE_SIZE);
    const double window_y0 = calculateMin(y, height_, map.height() * TILE_SIZE);

    // calculate initial and final tiles for X and Y directions
    const auto I0 = (size_t) floor(window_x0 / TILE_SIZE);
    const auto J0 = (size_t) floor(window_y0 / TILE_SIZE);
    const auto I1 = (size_t) ceil((window_x0 + width_) / TILE_SIZE);
    const auto J1 = (size_t) ceil((window_y0 + height_) / TILE_SIZE);

    for (size_t i = I0; i < map.width() && i < I1; ++i) {
        const int X = (int) (i * TILE_SIZE - window_x0);
        for (size_t j = J0; j < map.height() && j < J1; ++j) {
            const int Y = (int) (j * TILE_SIZE - window_y0);
            tile_draw(tileMapper_, map(i, j).type(), X, Y);
            action_draw(actionMapper_, map(i, j).action(), X, Y);
        }
    }
    // drawing the cursor
    const int X = (int) (x - window_x0);
    const int Y = (int) (y - window_y0);
    al_draw_filled_rectangle(X, Y, X + 3, Y + 3, COLORS[game::COLOR::BLACK]);

    // transfering rendered map to screen buffer
    al_draw_bitmap(buffer_.get(), 0, 0, 0);
}

void Graphic::flip() {
    al_flip_display();
    al_clear_to_color(COLORS[game::COLOR::BLACK]);
}
}
}
