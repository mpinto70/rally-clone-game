#pragma once

#include "gamelib/Keyboard.h"

namespace gamelib {
namespace allegro {

class Keyboard : public ::gamelib::Keyboard {
public:
    Keyboard();
    ~Keyboard() override;

    bool isKeyPressed(EKey keyCode) const override;
    std::set<EKey> keysPressed() const override;
};
}
}
