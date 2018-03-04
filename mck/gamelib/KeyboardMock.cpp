#include "KeyboardMock.h"

namespace gamelib {
namespace mck {

std::set<EKey> KeyboardMock::keys_;

KeyboardMock::~KeyboardMock() {
}

bool KeyboardMock::isKeyPressed(EKey keyCode) const {
    return keys_.find(keyCode) != keys_.end();
}

std::set<EKey> KeyboardMock::keysPressed() const {
    return keys_;
}

void KeyboardMock::add(EKey keyCode) {
    keys_.insert(keyCode);
}

void KeyboardMock::remove(EKey keyCode) {
    keys_.erase(keyCode);
}
}
}
