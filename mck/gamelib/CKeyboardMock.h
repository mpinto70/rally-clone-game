
#pragma once

#include "gamelib/IKeyboard.h"
#include <set>

namespace gamelib {
namespace mck {

class CKeyboardMock : public IKeyboard {
    public:
        ~CKeyboardMock() override;
        bool isKeyPressed(KEYS keyCode) override;
        static void add(KEYS keyCode);
        static void remove(KEYS keyCode);
    private:
        static std::set<KEYS> keys_;
};

}
}
