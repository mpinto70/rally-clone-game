
#include "CKeyboardMock.h"

namespace gamelib {
namespace mck {

std::set<EKey> CKeyboardMock::keys_;

CKeyboardMock::~CKeyboardMock() {
}

bool CKeyboardMock::isKeyPressed(EKey keyCode) const {
    return keys_.find(keyCode) != keys_.end();
}

std::set<EKey> CKeyboardMock::keysPressed() const {
    return keys_;
}

void CKeyboardMock::add(EKey keyCode) {
    keys_.insert(keyCode);
}

void CKeyboardMock::remove(EKey keyCode) {
    keys_.erase(keyCode);
}

}
}

