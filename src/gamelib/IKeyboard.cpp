
#include "IKeyboard.h"

namespace gamelib {

IKeyboard::~IKeyboard() {}
virtual bool isKeyPressed(KEYS keyCode) {return false;}
}

