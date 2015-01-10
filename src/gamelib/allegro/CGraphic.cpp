/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de gfx.
 */

#include "CGraphic.h"
#include "util/CException.h"

namespace gamelib {
namespace allegro {
CGraphic::CGraphic(unsigned int uiWidth, unsigned int uiHeight)
    : buffer_(nullptr) {
    using util::CException;

    set_color_depth(32);

    const int allegResult = set_gfx_mode(GFX_AUTODETECT_WINDOWED, uiWidth, uiHeight, 0, 0);
    if (allegResult != 0) // acho que é melhor tentar outras profundidades de cor, mas por enquanto interrompe
        throw CException("CGraphic::CGraphic - Error initializing screen", allegResult);

    // Cria buffer_ com a mesma resolução WxH da tela.
    buffer_ = create_bitmap(SCREEN_W, SCREEN_H);
    if (buffer_ == nullptr)
        throw CException("CGraphic::CGraphic - Error initializing system memory", -1);
}

CGraphic::~CGraphic() {
    destroy_bitmap(buffer_);
    buffer_ = nullptr;
}

}
}

