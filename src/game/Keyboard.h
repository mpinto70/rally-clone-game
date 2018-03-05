#pragma once

#include <set>

namespace game {

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
    virtual ~Keyboard() = default;
    virtual bool isKeyPressed(Key keyCode) const = 0;
    virtual std::set<Key> keysPressed() const = 0;
};
}
