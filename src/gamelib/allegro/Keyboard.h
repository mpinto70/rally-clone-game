#pragma once

#include "game/Keyboard.h"

namespace gamelib {
namespace allegro {

class Keyboard : public ::game::Keyboard {
public:
    Keyboard();
    ~Keyboard() override;

    [[nodiscard]] bool isKeyPressed(game::Key keyCode) const override;
    [[nodiscard]] std::set<game::Key> keysPressed() const override;
};
}
}
