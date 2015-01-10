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

}
}

