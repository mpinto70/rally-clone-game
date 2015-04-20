/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de gfx.
 */

#include "CGraphic.h"
#include "util/CException.h"
#include <map>

namespace gamelib {
namespace allegro {

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

CGraphic::CGraphic(unsigned int uiWidth,
                   unsigned int uiHeight,
                   const std::string & fonts_path)
    : buffer_(nullptr, destroy_bitmap),
      fontSystem_(nullptr, destroy_font),
      fontMenu_(nullptr, destroy_font) {
    using util::CException;

    set_color_depth(32);

    const int allegResult = set_gfx_mode(GFX_AUTODETECT_WINDOWED, uiWidth, uiHeight, 0, 0);
    if (allegResult != 0) // acho que é melhor tentar outras profundidades de cor, mas por enquanto interrompe
        throw CException("CGraphic::CGraphic - Error initializing screen", allegResult);

    // Cria buffer_ com a mesma resolução WxH da tela.
    buffer_.reset(create_bitmap(SCREEN_W, SCREEN_H));
    if (buffer_.get() == nullptr)
        throw CException("CGraphic::CGraphic - Error initializing system memory", -1);

    fontMenu_.reset(load_font((fonts_path + "/Menu_font.pcx").c_str(), nullptr, nullptr));
    if (fontMenu_.get() == nullptr)
        throw CException("CGraphic::CGraphic - Error initializing menu font", -2);

    fontSystem_.reset(load_font((fonts_path + "/Menu_font.pcx").c_str(), nullptr, nullptr));
    if (fontSystem_.get() == nullptr)
        throw CException("CGraphic::CGraphic - Error initializing system font", -3);

    initColor();
    rectfill(buffer_.get(), 0, 0, SCREEN_W, SCREEN_H, COLORS[COLOR::BLUE]);
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

void CGraphic::flip() {
    flipBuffer(buffer_.get());
}

}
}

