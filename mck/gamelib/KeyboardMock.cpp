#include "KeyboardMock.h"

namespace gamelib {
namespace mck {

std::set<Key> KeyboardMock::keys_;

KeyboardMock::~KeyboardMock() {
}

bool KeyboardMock::isKeyPressed(Key keyCode) const {
    return keys_.find(keyCode) != keys_.end();
}

std::set<Key> KeyboardMock::keysPressed() const {
    return keys_;
}

void KeyboardMock::add(Key keyCode) {
    keys_.insert(keyCode);
}

void KeyboardMock::remove(Key keyCode) {
    keys_.erase(keyCode);
}
}
}
