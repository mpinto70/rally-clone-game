#pragma once

#include "game/GameLib.h"
#include "gamelib/allegro/Graphic.h"
#include "gamelib/allegro/Keyboard.h"
#include "gamelib/allegro/Sound.h"
#include "gamelib/allegro/Timer.h"

#include <memory>

namespace gamelib {
namespace allegro {

class GameLib : public ::game::GameLib {
public:
    GameLib(unsigned int width,
          unsigned int height,
          const std::string& path_to_data);
    ~GameLib() override = default;

    Graphic& graphic() override { return *graphic_; }
    Sound& sound() override { return *sound_; }
    Timer& timer() override { return *timer_; }
    Keyboard& keyboard() override { return *keyboard_; }

private:
    std::unique_ptr<ALLEGRO_DISPLAY, void (*)(ALLEGRO_DISPLAY*)> display_;
    std::unique_ptr<Graphic> graphic_;
    std::unique_ptr<Keyboard> keyboard_;
    std::unique_ptr<Sound> sound_;
    std::unique_ptr<Timer> timer_;
};
}
}
