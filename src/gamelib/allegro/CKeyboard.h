/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de input.
*/

#pragma once

#include "gamelib/IKeyboard.h"

namespace gamelib {
namespace allegro {

class CKeyboard : public IKeyboard {
public:
    CKeyboard();
    ~CKeyboard() override;

    bool isKeyPressed(EKey keyCode) const override;
    std::set<EKey> keysPressed() const override;
};
}
}
