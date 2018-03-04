#include "Keyboard.h"

#include "util/Util.h"
#include "util/Exception.h"

#include <allegro.h>

namespace gamelib {
namespace allegro {

Keyboard::Keyboard() {
}

Keyboard::~Keyboard() {
}

static unsigned int translateKey(EKey keyCode) {
    switch (keyCode) {
        case EKey::ENTER:
            return KEY_ENTER;
        case EKey::LEFT:
            return KEY_LEFT;
        case EKey::RIGHT:
            return KEY_RIGHT;
        case EKey::UP:
            return KEY_UP;
        case EKey::DOWN:
            return KEY_DOWN;
        case EKey::SPACE:
            return KEY_SPACE;
        case EKey::ESCAPE:
            return KEY_ESC;
        case EKey::LAST:
            return -1;
    }
    return -1;
}

bool Keyboard::isKeyPressed(EKey keyCode) const {
    const unsigned int allegroKey = translateKey(keyCode);

    return (allegroKey != (unsigned int) -1 && key[allegroKey] != 0);
}

std::set<EKey> Keyboard::keysPressed() const {
    std::set<EKey> res;
    for (auto key : util::CEnumIterator<EKey>()) {
        if (isKeyPressed(key)) {
            res.insert(key);
        }
    }
    return res;
}
}
}
