#include "GameLib.h"

#include "util/Exception.h"

#include <allegro.h>

namespace gamelib {
namespace allegro {

GameLib::GameLib(unsigned int width,
      unsigned int height,
      const std::string& path_to_data)
      : graphic_(nullptr),
        keyboard_(nullptr),
        sound_(nullptr),
        timer_(nullptr) {
    using util::Exception;
    int allegResult = allegro_init();
    if (allegResult != 0) {
        throw Exception("CGameLib - Error initializing graphics", allegResult);
    }

    allegResult = install_keyboard();
    if (allegResult != 0) {
        throw util::Exception("CGameLib - Error initializing keyboard", allegResult);
    }

    allegResult = install_timer();
    if (allegResult != 0) {
        throw util::Exception("CGameLib - Error initializing timer", allegResult);
    }

    set_color_depth(32);

    allegResult = set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);
    if (allegResult != 0) {
        throw Exception("CGameLib - Error initializing screen", allegResult);
    }

    keyboard_ = new Keyboard();
    timer_ = new Timer();
    sound_ = new Sound();
    graphic_ = new Graphic(path_to_data + "/stages/common");
}

GameLib::~GameLib() {
    delete graphic_;
    delete sound_;
    delete timer_;
    delete keyboard_;

    allegro_exit();
}
}
}
