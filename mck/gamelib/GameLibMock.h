#pragma once

#include "gamelib/GameLib.h"

#include <memory>

namespace gamelib {
namespace mck {

class GameLibMock : public GameLib {
public:
    GameLibMock(std::unique_ptr<Graphic>& graphic,
          std::unique_ptr<Sound>& sound,
          std::unique_ptr<Timer>& timer,
          std::unique_ptr<Keyboard>& keyboard);
    ~GameLibMock() override;
    Graphic& graphic() override { return *graphic_; }
    Sound& sound() override { return *sound_; }
    Timer& timer() override { return *timer_; }
    Keyboard& keyboard() override { return *keyboard_; }

private:
    std::unique_ptr<Graphic> graphic_;
    std::unique_ptr<Sound> sound_;
    std::unique_ptr<Timer> timer_;
    std::unique_ptr<Keyboard> keyboard_;
};
}
}
