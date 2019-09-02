#include "Keyboard.h"

#include "util/Exception.h"
#include "util/Util.h"

#include <allegro5/allegro.h>

namespace gamelib {
namespace allegro {

Keyboard::Keyboard() = default;

Keyboard::~Keyboard() = default;

static int translateKey(game::Key keyCode) {
    switch (keyCode) {
        case game::Key::ENTER: return ALLEGRO_KEY_ENTER;
        case game::Key::LEFT: return ALLEGRO_KEY_LEFT;
        case game::Key::RIGHT: return ALLEGRO_KEY_RIGHT;
        case game::Key::UP: return ALLEGRO_KEY_UP;
        case game::Key::DOWN: return ALLEGRO_KEY_DOWN;
        case game::Key::SPACE: return ALLEGRO_KEY_SPACE;
        case game::Key::ESCAPE: return ALLEGRO_KEY_ESCAPE;
        case game::Key::LAST: return -1;
    }
    return -1;
}

bool Keyboard::isKeyPressed(game::Key keyCode) const {
    const int allegroKey = translateKey(keyCode);
    ALLEGRO_KEYBOARD_STATE state;
    al_get_keyboard_state(&state);

    return (allegroKey != -1 && al_key_down(&state, allegroKey));
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
