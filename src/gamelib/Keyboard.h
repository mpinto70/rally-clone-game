#pragma once

#include <set>

namespace gamelib {

enum class EKey : unsigned char {
    ENTER = 1,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    SPACE,
    ESCAPE,
    LAST,
    FIRST = ENTER
};

class Keyboard {
public:
    virtual ~Keyboard() = 0;
    virtual bool isKeyPressed(EKey keyCode) const = 0;
    virtual std::set<EKey> keysPressed() const = 0;
};
}
