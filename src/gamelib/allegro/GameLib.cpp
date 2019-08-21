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
        throw Exception("GameLib - Error initializing graphics", allegResult);
    }

    allegResult = install_keyboard();
    if (allegResult != 0) {
        throw util::Exception("GameLib - Error initializing keyboard", allegResult);
    }

    allegResult = install_timer();
    if (allegResult != 0) {
        throw util::Exception("GameLib - Error initializing timer", allegResult);
    }

    set_color_depth(32);

    allegResult = set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);
    if (allegResult != 0) {
        throw Exception("GameLib - Error initializing screen", allegResult);
    }

    keyboard_ = std::make_unique<Keyboard>();
    timer_ = std::make_unique<Timer>();
    sound_ = std::make_unique<Sound>();
    graphic_ = std::make_unique<Graphic>(path_to_data + "/stages/common");
}

GameLib::~GameLib() {
    graphic_.reset();
    sound_.reset();
    timer_.reset();
    keyboard_.reset();

    allegro_exit();
}
}
}
