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
    GameLib(const std::string& commonPath,
          unsigned int width,
          unsigned int height,
          bmp::TileSource tileSource = bmp::TileSource::GREEN,
          bmp::CarSource carSource = bmp::CarSource::PLAYER_1,
          bmp::CarSource enemySource = bmp::CarSource::ENEMY_1);
    ~GameLib() override;

    Graphic& graphic() override { return *graphic_; }
    Sound& sound() override { return *sound_; }
    Timer& timer() override { return *timer_; }
    Keyboard& keyboard() override { return *keyboard_; }

    ALLEGRO_EVENT_QUEUE& eventQueue() {
        return *eventQueue_;
    }

private:
    std::unique_ptr<Graphic> graphic_;
    std::unique_ptr<Keyboard> keyboard_;
    std::unique_ptr<Sound> sound_;
    std::unique_ptr<Timer> timer_;
    EVENT_QUEUE_PTR eventQueue_;
};
}
}
