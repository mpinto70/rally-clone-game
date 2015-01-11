/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de input.
 */

#include "CKeyboard.h"
#include "util/CException.h"
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

static unsigned int translateKey(KEYS keyCode) {
    switch (keyCode) {
        case KEYS::ENTER:
            return KEY_ENTER;
        case KEYS::LEFT:
            return KEY_LEFT;
        case KEYS::RIGHT:
            return KEY_RIGHT;
        case KEYS::UP:
            return KEY_UP;
        case KEYS::DOWN:
            return KEY_DOWN;
        case KEYS::SPACE:
            return KEY_SPACE;
        default:
            return -1;
    }
}

bool CKeyboard::isKeyPressed(KEYS keyCode) {
    const unsigned int allegroKey = translateKey(keyCode);

    return (allegroKey != (unsigned int) - 1 && key[allegroKey] != 0);
}

}
}

