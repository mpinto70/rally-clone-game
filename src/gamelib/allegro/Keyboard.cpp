#include "Keyboard.h"

#include "util/Exception.h"
#include "util/Util.h"

#include <allegro.h>

namespace gamelib {
namespace allegro {

Keyboard::Keyboard() {
}

Keyboard::~Keyboard() {
}

static unsigned int translateKey(Key keyCode) {
    switch (keyCode) {
        case Key::ENTER:
            return KEY_ENTER;
        case Key::LEFT:
            return KEY_LEFT;
        case Key::RIGHT:
            return KEY_RIGHT;
        case Key::UP:
            return KEY_UP;
        case Key::DOWN:
            return KEY_DOWN;
        case Key::SPACE:
            return KEY_SPACE;
        case Key::ESCAPE:
            return KEY_ESC;
        case Key::LAST:
            return -1;
    }
    return -1;
}

bool Keyboard::isKeyPressed(Key keyCode) const {
    const unsigned int allegroKey = translateKey(keyCode);

    return (allegroKey != (unsigned int) -1 && key[allegroKey] != 0);
}

std::set<Key> Keyboard::keysPressed() const {
    std::set<Key> res;
    for (auto key : util::EnumIterator<Key>()) {
        if (isKeyPressed(key)) {
            res.insert(key);
        }
    }
    return res;
}
}
}
