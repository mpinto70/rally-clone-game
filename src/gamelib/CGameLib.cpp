/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de input/gfx/sfx/misc.
 */

#include "CGameLib.h"
#include "util/CException.h"

namespace gamelib {

GameLib::GameLib(unsigned int uiWidth, unsigned int uiHeight)
    : buffer_(nullptr) {
    int allegResult = allegro_init();

    if (allegResult != 0)
        throw CException("Error initializing graphics", allegResult);

    allegResult = install_keyboard();
    if (allegResult != 0)
        throw CException("Error initializing keyboard", allegResult);

    allegResult += install_timer();
    if (allegResult != 0)
        throw CException("Error initializing timer", allegResult);

    allegResult = install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, nullptr);

    if (allegResult != 0)
        throw CException("Error initializing sound", allegResult);

    set_color_depth(32);
    allegResult = set_gfx_mode(GFX_AUTODETECT_WINDOWED, uiWidth, uiHeight, 0, 0);
    if (allegResult != 0) // acho que é melhor tentar outras profundidades de cor, mas por enquanto interrompe
        throw CException("Error initializing screen", allegResult);

    // Cria buffer_ com a mesma resolução WxH da tela.
    buffer_ = create_bitmap(SCREEN_W, SCREEN_H);
    if (buffer_ == nullptr)
        throw CException("Error initializing system memory", -1);
}

GameLib::~GameLib() {
    destroy_bitmap(buffer_);
    buffer_ = nullptr;

    // Vale a pena? o processo tá morrendo... Do manual:
    // Note that after you call this function, other functions like destroy_bitmap() will most likely crash.
    // This is a problem for C++ global destructors, which usually get called after atexit(), so don't put
    // Allegro calls in them. You can write the destructor code in another method which you can manually call
    // before your program exits, avoiding this problem.
    allegro_exit();
}

}

