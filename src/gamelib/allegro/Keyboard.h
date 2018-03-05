#pragma once

#include "game/Keyboard.h"

namespace gamelib {
namespace allegro {

class Keyboard : public ::game::Keyboard {
public:
    Keyboard();
    ~Keyboard() override;

    bool isKeyPressed(game::Key keyCode) const override;
    std::set<game::Key> keysPressed() const override;
};
}
}
