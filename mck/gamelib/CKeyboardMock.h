
#pragma once

#include "gamelib/IKeyboard.h"

namespace gamelib {
namespace mck {

class CKeyboardMock : public IKeyboard {
    public:
        ~CKeyboardMock() override;
        bool isKeyPressed(KEYS keyCode) override { return false; }
};

}
}
