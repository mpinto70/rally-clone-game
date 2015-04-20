
#pragma once

#include "gamelib/IKeyboard.h"
#include <set>

namespace gamelib {
namespace mck {

class CKeyboardMock : public IKeyboard {
    public:
        ~CKeyboardMock() override;
        bool isKeyPressed(EKey keyCode) const override;
        std::set<EKey> keysPressed() const override;

        static void add(EKey keyCode);
        static void remove(EKey keyCode);
    private:
        static std::set<EKey> keys_;
};

}
}
