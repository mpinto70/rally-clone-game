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

static unsigned int translateKey(game::Key keyCode) {
    switch (keyCode) {
        case game::Key::ENTER: return KEY_ENTER;
        case game::Key::LEFT: return KEY_LEFT;
        case game::Key::RIGHT: return KEY_RIGHT;
        case game::Key::UP: return KEY_UP;
        case game::Key::DOWN: return KEY_DOWN;
        case game::Key::SPACE: return KEY_SPACE;
        case game::Key::ESCAPE: return KEY_ESC;
        case game::Key::LAST: return -1;
    }
    return -1;
}

bool Keyboard::isKeyPressed(game::Key keyCode) const {
    const unsigned int allegroKey = translateKey(keyCode);

    return (allegroKey != (unsigned int) -1 && key[allegroKey] != 0);
}

std::set<game::Key> Keyboard::keysPressed() const {
    std::set<game::Key> res;
    for (auto key : util::EnumIterator<game::Key>()) {
        if (isKeyPressed(key)) {
            res.insert(key);
        }
    }
    return res;
}
}
}
