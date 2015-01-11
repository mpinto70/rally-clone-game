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

bool CKeyboard::isKeyPressed(KEYS keyCode) {
  unsigned int keyCode = 0;

  switch(keyCode) {
    case IKeyboard::GLIB_KEY_ENTER:
	  keyCode = KEY_ENTER;
	break;
    case IKeyboard::GLIB_KEY_LEFT:
	  keyCode = KEY_LEFT;
	break;
    case IKeyboard::GLIB_KEY_RIGHT:
	  keyCode = KEY_RIGHT;
	break;
    case IKeyboard::GLIB_KEY_UP:
	  keyCode = KEY_UP;
	break;
    case IKeyboard::GLIB_KEY_DOWN:
	  keyCode = KEY_DOWN;
	break;
    case IKeyboard::GLIB_KEY_SPACE:
	  keyCode = KEY_SPACE;
	break;
  }
  
  return (key[keyCode] != 0);
}

}
}

