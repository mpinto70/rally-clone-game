#include "GameLib.h"

#include "util/Exception.h"

#include <allegro5/allegro.h>

namespace gamelib {
namespace allegro {

GameLib::GameLib(unsigned int width,
      unsigned int height,
      const std::string& path_to_data)
      : display_(nullptr, al_destroy_display),
      graphic_(nullptr),
        keyboard_(nullptr),
        sound_(nullptr),
        timer_(nullptr) {
    using util::Exception;
    int allegResult = al_init();
    if (allegResult != 0) {
        throw Exception("GameLib - Error initializing graphics", allegResult);
    }

    display_.reset(al_create_display(width, height));
    if (display_ == nullptr) {
        throw util::Exception("GameLib - Error creating display", -1);
    }
    allegResult = al_install_keyboard();
    if (allegResult != 0) {
        throw util::Exception("GameLib - Error initializing keyboard", allegResult);
    }

    keyboard_ = std::make_unique<Keyboard>();
    timer_ = std::make_unique<Timer>();
    sound_ = std::make_unique<Sound>();
    graphic_ = std::make_unique<Graphic>(path_to_data + "/stages/common", width, height);
}
}
}
