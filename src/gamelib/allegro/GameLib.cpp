#include "GameLib.h"

#include "util/Exception.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

namespace gamelib {
namespace allegro {

namespace {
DISPLAY_PTR initDisplay(unsigned width, unsigned height) {
    if (not al_install_system(ALLEGRO_VERSION_INT, nullptr))
        throw util::Exception("Could not init Allegro", -1);
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();

    return createElement(al_create_display, al_destroy_display, width, height);
}
}

GameLib::GameLib(const std::string& commonPath,
      unsigned int width,
      unsigned int height,
      bmp::TileSource tileSource,
      bmp::CarSource carSource,
      bmp::CarSource enemySource)
      : graphic_(std::make_unique<Graphic>(initDisplay(width, height), commonPath, tileSource, carSource, enemySource)),
        keyboard_(std::make_unique<Keyboard>()),
        sound_(std::make_unique<Sound>()),
        timer_(std::make_unique<Timer>()),
        eventQueue_(createElement(al_create_event_queue, al_destroy_event_queue)) {
    al_register_event_source(eventQueue_.get(), al_get_keyboard_event_source());
    al_register_event_source(eventQueue_.get(), al_get_mouse_event_source());
    al_register_event_source(eventQueue_.get(), al_get_display_event_source(&graphic_->display()));
}

GameLib::~GameLib() {
    timer_.reset();
    sound_.reset();
    keyboard_.reset();
    graphic_.reset();
    eventQueue_.reset();

    al_uninstall_system();
}
}
}
