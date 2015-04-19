
#include "CKeyboardMock.h"

namespace gamelib {
namespace mck {

std::set<KEYS> CKeyboardMock::keys_;

CKeyboardMock::~CKeyboardMock() {
}

bool CKeyboardMock::isKeyPressed(KEYS keyCode) {
    return keys_.find(keyCode) != keys_.end();
}

void CKeyboardMock::add(KEYS keyCode) {
    keys_.insert(keyCode);
}

void CKeyboardMock::remove(KEYS keyCode) {
    keys_.erase(keyCode);
}

}
}

