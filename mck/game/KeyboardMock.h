#pragma once

#include "game/Keyboard.h"

#include <set>

namespace game {
namespace mck {

class KeyboardMock : public Keyboard {
public:
    ~KeyboardMock() override;
    bool isKeyPressed(Key keyCode) const override;
    std::set<Key> keysPressed() const override;

    static void add(Key keyCode);
    static void remove(Key keyCode);

private:
    static std::set<Key> keys_;
};
}
}
