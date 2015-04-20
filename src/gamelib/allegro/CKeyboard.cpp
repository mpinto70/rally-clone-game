/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de input.
 */

#include "CKeyboard.h"

#include "util/CException.h"
#include "util/EUtil.h"

#include <allegro.h>

namespace gamelib {
namespace allegro {

CKeyboard::CKeyboard() {
    const int allegResult = install_keyboard();
    if (allegResult != 0)
        throw util::CException("CKeyboard::CKeyboard - Error initializing keyboard", allegResult);
}

CKeyboard::~CKeyboard() {
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

bool CKeyboard::isKeyPressed(EKey keyCode) const {
    const unsigned int allegroKey = translateKey(keyCode);

    return (allegroKey != (unsigned int) - 1 && key[allegroKey] != 0);
}

std::set<EKey> CKeyboard::keysPressed() const {
    std::set<EKey> res;
    for (auto key : util::CEnumIterator<EKey>()) {
        if (isKeyPressed(key))
            res.insert(key);
    }
    return res;
}

}
}

