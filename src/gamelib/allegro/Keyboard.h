#pragma once

#include "gamelib/Keyboard.h"

namespace gamelib {
namespace allegro {

class Keyboard : public ::gamelib::Keyboard {
public:
    Keyboard();
    ~Keyboard() override;

    bool isKeyPressed(Key keyCode) const override;
    std::set<Key> keysPressed() const override;
};
}
}
