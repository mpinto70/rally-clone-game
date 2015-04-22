/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de gfx.
 */

#include "CGraphic.h"
#include "util/CException.h"
#include <map>

namespace gamelib {
namespace allegro {

static constexpr unsigned TILE_SIZE     = 32;       ///< tile size in pixels
static constexpr unsigned TILE_GAP      = 2;        ///< gap between tiles
static constexpr unsigned ACTION_SIZE   = 32;       ///< action size in pixels
static constexpr unsigned ACTION_GAP    = 1;        ///< gap between actions

static std::map<COLOR, int> COLORS;
static void initColor() {
    COLORS[COLOR::BLACK]    = makecol32(0,   0,   0);
    COLORS[COLOR::RED]      = makecol32(255, 0,   0);
    COLORS[COLOR::GREEN]    = makecol32(0,   255, 0);
    COLORS[COLOR::BLUE]     = makecol32(0,   0,   255);
    COLORS[COLOR::WHITE]    = makecol32(255, 255, 255);
}

static int translate(COLOR color) {
    return COLORS[color];
}

static void flipBuffer(BITMAP * buffer) {
    vsync();
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    clear_bitmap(buffer);
}

CGraphic::CGraphic(const std::string & common_path)
    : buffer_(nullptr, destroy_bitmap),
      fontSystem_(nullptr, destroy_font),
      fontMenu_(nullptr, destroy_font),
      tileMapper_(common_path + "/tileset.bmp", TILE_SIZE, TILE_SIZE, TILE_GAP),
      actionMapper_(common_path + "/actions.bmp", ACTION_SIZE, ACTION_SIZE, ACTION_GAP) {
    using util::CException;
    // Cria buffer_ com a mesma resolução WxH da tela.
    buffer_.reset(create_bitmap(SCREEN_W, SCREEN_H));
    if (buffer_.get() == nullptr)
        throw CException("CGraphic::CGraphic - Error initializing system memory", -1);

    fontMenu_.reset(load_font((common_path + "/Menu_font.pcx").c_str(), nullptr, nullptr));
    if (fontMenu_.get() == nullptr)
        throw CException("CGraphic::CGraphic - Error initializing menu font", -2);

    fontSystem_.reset(load_font((common_path + "/Menu_font.pcx").c_str(), nullptr, nullptr));
    if (fontSystem_.get() == nullptr)
        throw CException("CGraphic::CGraphic - Error initializing system font", -3);

    initColor();
    rectfill(buffer_.get(), 0, 0, SCREEN_W, SCREEN_H, COLORS[COLOR::RED]);
    flipBuffer(buffer_.get());
}

CGraphic::~CGraphic() {
}

void CGraphic::printText(const std::string & text,
                         const GFONT gfont,
                         const unsigned x,
                         const unsigned y,
                         COLOR foreground,
                         COLOR background) {
    if (x > width() || y > height())
        return;

    if (text.empty())
        return;

    const FONT * font = gfont == GFONT::MENU_FONT ? fontMenu_.get() : fontSystem_.get();
    textprintf_ex(buffer_.get(), font, x, y, translate(foreground), translate(background), "%s", text.c_str());
}

template <typename MAPPER>
static void mapper_draw(BITMAP * bmp,
                        const MAPPER & mapper,
                        const typename MAPPER::enum_type type,
                        const int x,
                        const int y) {
    const auto sub_bmp = mapper[type];
    draw_sprite(bmp, sub_bmp, x, y);
}

static void tile_draw(BITMAP * bmp,
                      const gamelib::allegro::bmp::CTileMapper & mapper,
                      const map::ETileType type,
                      const int x,
                      const int y) {
    mapper_draw(bmp, mapper, type, x, y);
}

static void action_draw(BITMAP * bmp,
                        const gamelib::allegro::bmp::CActionMapper & mapper,
                        const map::EAction action,
                        const int x,
                        const int y) {
    mapper_draw(bmp, mapper, action, x, y);
}

void CGraphic::draw(const map::CMap & map,
                    const size_t x,
                    const size_t y) {
    for (size_t i = 0; i < map.width() && i * TILE_SIZE < width(); ++i) {
        const auto X = i * TILE_SIZE;
        for (size_t j = 0; j < map.height() && j * TILE_SIZE < height(); ++j) {
            const auto Y = j * TILE_SIZE;
            tile_draw(buffer_.get(), tileMapper_, map(i, j).type(), X, Y);
            action_draw(buffer_.get(), actionMapper_, map(i, j).action(), X, Y);
        }
    }
}

void CGraphic::flip() {
    flipBuffer(buffer_.get());
}

}
}

