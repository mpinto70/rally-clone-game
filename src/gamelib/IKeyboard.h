
#pragma once

namespace gamelib {

enum class KEYS : unsigned char {
    ENTER = 1,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    SPACE,
    ESCAPE
};

class IKeyboard {
    public:
        virtual ~IKeyboard() = 0;
        virtual bool isKeyPressed(KEYS keyCode) = 0;
};

}

