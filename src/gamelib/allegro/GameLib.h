#pragma once

#include "game/GameLib.h"
#include "gamelib/allegro/Graphic.h"
#include "gamelib/allegro/Keyboard.h"
#include "gamelib/allegro/Sound.h"
#include "gamelib/allegro/Timer.h"

namespace gamelib {
namespace allegro {

class GameLib : public ::game::GameLib {
public:
    GameLib(unsigned int width,
          unsigned int height,
          const std::string& path_to_data);
    ~GameLib() override;

    Graphic& graphic() override { return *graphic_; }
    Sound& sound() override { return *sound_; }
    Timer& timer() override { return *timer_; }
    Keyboard& keyboard() override { return *keyboard_; }

private:
    Graphic* graphic_;
    Keyboard* keyboard_;
    Sound* sound_;
    Timer* timer_;
};
}
}
