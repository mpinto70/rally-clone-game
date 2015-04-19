/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de input/gfx/sfx/misc.
 */

#include "CGameLib.h"
#include "util/CException.h"
#include <allegro.h>

namespace gamelib {
namespace allegro {

CGameLib::CGameLib(unsigned int width,
                   unsigned int height,
                   const std::string & path_to_data)
    : graphic_(nullptr),
      keyboard_(nullptr),
      sound_(nullptr),
      timer_(nullptr) {
    using util::CException;
    const int allegResult = allegro_init();
    if (allegResult != 0)
        throw CException("CGameLib::CGameLib - Error initializing graphics", allegResult);

    keyboard_ = new CKeyboard();
    timer_ = new CTimer();
    sound_ = new CSound();
    graphic_ = new CGraphic(width, height, path_to_data + "/stages/common");
}

CGameLib::~CGameLib() {
    delete graphic_;
    delete sound_;
    delete timer_;
    delete keyboard_;

    allegro_exit();
}

}
}

