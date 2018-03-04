#pragma once

#include <set>

namespace gamelib {

enum class Key : unsigned char {
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
    virtual bool isKeyPressed(Key keyCode) const = 0;
    virtual std::set<Key> keysPressed() const = 0;
};
}
