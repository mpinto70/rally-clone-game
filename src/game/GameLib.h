#pragma once

#include "game/Graphic.h"
#include "game/Keyboard.h"
#include "game/Sound.h"
#include "game/Timer.h"

namespace game {

class GameLib {
public:
    virtual ~GameLib() = default;
    virtual Graphic& graphic() = 0;
    virtual Sound& sound() = 0;
    virtual Timer& timer() = 0;
    virtual Keyboard& keyboard() = 0;
};
}
