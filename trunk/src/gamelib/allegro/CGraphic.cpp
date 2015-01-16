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

CGraphic::CGraphic(unsigned int uiWidth, unsigned int uiHeight)
    : buffer_(nullptr),
      fontSystem_(nullptr),
      fontMenu_(nullptr) {
    using util::CException;

    set_color_depth(32);

    const int allegResult = set_gfx_mode(GFX_AUTODETECT_WINDOWED, uiWidth, uiHeight, 0, 0);
    if (allegResult != 0) // acho que é melhor tentar outras profundidades de cor, mas por enquanto interrompe
        throw CException("CGraphic::CGraphic - Error initializing screen", allegResult);

    // Cria buffer_ com a mesma resolução WxH da tela.
    buffer_ = create_bitmap(SCREEN_W, SCREEN_H);
    if (buffer_ == nullptr)
        throw CException("CGraphic::CGraphic - Error initializing system memory", -1);

    fontMenu_ = load_font(RALLY_ROOT "/Stuff/Menu_font.pcx", nullptr, nullptr);
    if (fontMenu_ == nullptr)
        throw CException("CGraphic::CGraphic - Error initializing font subsystem", -2);

    fontSystem_ = load_font(RALLY_ROOT "/Stuff/Menu_font.pcx", nullptr, nullptr);
    if (fontSystem_ == nullptr)
        throw CException("CGraphic::CGraphic - Error initializing font subsystem", -3);

    initColor();
}

CGraphic::~CGraphic() {
    destroy_bitmap(buffer_);
    buffer_ = nullptr;
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

    const FONT * font = gfont == GFONT::MENU_FONT ? fontMenu_ : fontSystem_;
    textprintf_ex(buffer_, font, x, y, translate(foreground), translate(background), "%s", text.c_str());
}

}
}

