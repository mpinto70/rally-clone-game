#include "Graphic.h"

#include "util/Exception.h"

#include <map>
#include <cmath>

namespace gamelib {
namespace allegro {

static constexpr unsigned TILE_SIZE = 32;    ///< tile size in pixels
static constexpr unsigned TILE_GAP = 2;      ///< gap between tiles
static constexpr unsigned ACTION_SIZE = 32;  ///< action size in pixels
static constexpr unsigned ACTION_GAP = 1;    ///< gap between actions
static constexpr unsigned SIDE_BAR_W = 200;  ///< width of the side bar
static constexpr unsigned BOTTOM_BAR_H = 50; ///< width of the side bar

static std::map<game::COLOR, int> COLORS;
static void initColor() {
    COLORS[game::COLOR::RED] = makecol32(255, 0, 0);
    COLORS[game::COLOR::WINE] = makecol32(64, 0, 0);
    COLORS[game::COLOR::GREEN] = makecol32(0, 255, 0);
    COLORS[game::COLOR::DARKGREEN] = makecol32(0, 64, 0);
    COLORS[game::COLOR::BLUE] = makecol32(0, 0, 255);
    COLORS[game::COLOR::DARKBLUE] = makecol32(0, 0, 64);
    COLORS[game::COLOR::WHITE] = makecol32(255, 255, 255);
    COLORS[game::COLOR::GRAY] = makecol32(128, 128, 128);
    COLORS[game::COLOR::DARKGRAY] = makecol32(64, 64, 64);
    COLORS[game::COLOR::BLACK] = makecol32(0, 0, 0);
}

static int translate(game::COLOR color) {
    return COLORS[color];
}

Graphic::Graphic(const std::string& common_path)
      : buffer_(nullptr, destroy_bitmap),
        bufferMap_(nullptr, destroy_bitmap),
        fontSystem_(nullptr, destroy_font),
        fontMenu_(nullptr, destroy_font),
        tileMapper_(common_path + "/tileset.bmp", TILE_SIZE, TILE_SIZE, TILE_GAP),
        actionMapper_(common_path + "/actions.bmp", ACTION_SIZE, ACTION_SIZE, ACTION_GAP) {
    using util::Exception;
    // creates the buffer of the entire screen
    buffer_.reset(create_bitmap(SCREEN_W, SCREEN_H));
    if (buffer_.get() == nullptr) {
        throw Exception("Graphic::Graphic - Error initializing main screen buffer", -1);
    }

    // creates the buffer for the map.
    bufferMap_.reset(create_bitmap(SCREEN_W - SIDE_BAR_W, SCREEN_H - BOTTOM_BAR_H));
    if (bufferMap_.get() == nullptr) {
        throw Exception("Graphic::Graphic - Error initializing map buffer", -1);
    }

    fontMenu_.reset(load_font((common_path + "/Menu_font.pcx").c_str(), nullptr, nullptr));
    if (fontMenu_.get() == nullptr) {
        throw Exception("Graphic::Graphic - Error initializing menu font [" + common_path + "/Menu_font.pcx]", -2);
    }

    fontSystem_.reset(load_font((common_path + "/Menu_font.pcx").c_str(), nullptr, nullptr));
    if (fontSystem_.get() == nullptr) {
        throw Exception("Graphic::Graphic - Error initializing system font [" + common_path + "/Menu_font.pcx]", -3);
    }

    initColor();
}

Graphic::~Graphic() {
}

void Graphic::printText(const std::string& text,
      const game::GFONT gfont,
      const unsigned x,
      const unsigned y,
      const game::COLOR foreground,
      const game::COLOR background) {
    if (x > width() || y > height()) {
        return;
    }

    if (text.empty()) {
        return;
    }

    const FONT* font = gfont == game::GFONT::MENU_FONT ? fontMenu_.get() : fontSystem_.get();
    textprintf_ex(buffer_.get(), font, x, y, translate(foreground), translate(background), "%s", text.c_str());
}

template <typename MAPPER>
static void mapper_draw(BITMAP* bmp,
      const MAPPER& mapper,
      const typename MAPPER::enum_type type,
      const int x,
      const int y) {
    const auto sub_bmp = mapper[type];
    draw_sprite(bmp, sub_bmp, x, y);
}

static void tile_draw(BITMAP* bmp,
      const gamelib::allegro::bmp::TileMapper& mapper,
      const map::TileType type,
      const int x,
      const int y) {
    mapper_draw(bmp, mapper, type, x, y);
}

static void action_draw(BITMAP* bmp,
      const gamelib::allegro::bmp::ActionMapper& mapper,
      const map::Action action,
      const int x,
      const int y) {
    mapper_draw(bmp, mapper, action, x, y);
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
    rectfill(buffer_.get(), 0, 0, buffer_->w, buffer_->h, COLORS[game::COLOR::WINE]);
    rect(buffer_.get(), 0, 0, bufferMap_->w + 3, bufferMap_->h + 3, COLORS[game::COLOR::WHITE]);
    rect(buffer_.get(), 1, 1, bufferMap_->w + 2, bufferMap_->h + 2, COLORS[game::COLOR::WHITE]);

    // ratio between the tile size on screen and the number of logical divisions inside tile
    const double ratio_S_T = (double) TILE_SIZE / parts;

    // converting cursor logical coordinate to screen coordinate (if screen was full size)
    const double x = x_cursor * ratio_S_T;
    const double y = y_cursor * ratio_S_T;

    // calculation window that will be shown
    const double window_x0 = calculateMin(x, bufferMap_->w, map.width() * TILE_SIZE);
    const double window_y0 = calculateMin(y, bufferMap_->h, map.height() * TILE_SIZE);

    // calculate initial and final tiles for X and Y directions
    const size_t I0 = (size_t) floor(window_x0 / TILE_SIZE);
    const size_t J0 = (size_t) floor(window_y0 / TILE_SIZE);
    const size_t I1 = (size_t) ceil((window_x0 + bufferMap_->w) / TILE_SIZE);
    const size_t J1 = (size_t) ceil((window_y0 + bufferMap_->h) / TILE_SIZE);

    for (size_t i = I0; i < map.width() && i < I1; ++i) {
        const int X = (int) (i * TILE_SIZE - window_x0);
        for (size_t j = J0; j < map.height() && j < J1; ++j) {
            const int Y = (int) (j * TILE_SIZE - window_y0);
            tile_draw(bufferMap_.get(), tileMapper_, map(i, j).type(), X, Y);
            action_draw(bufferMap_.get(), actionMapper_, map(i, j).action(), X, Y);
        }
    }
    // drawing the cursor
    const int X = (int) (x - window_x0);
    const int Y = (int) (y - window_y0);
    rectfill(bufferMap_.get(), X, Y, X + 3, Y + 3, COLORS[game::COLOR::BLACK]);

    // transfering rendered map to screen buffer
    blit(bufferMap_.get(), buffer_.get(), 0, 0, 2, 2, bufferMap_->w, bufferMap_->h);
}

void Graphic::flip() {
    vsync();
    blit(buffer_.get(), screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    clear_bitmap(buffer_.get());
    clear_bitmap(bufferMap_.get());
}
}
}
