#pragma once

#include "gamelib/Graphic.h"
#include "gamelib/Keyboard.h"
#include "gamelib/Sound.h"
#include "gamelib/Timer.h"

namespace game {

class GameLib {
public:
    virtual ~GameLib() = 0;
    virtual Graphic& graphic() = 0;
    virtual Sound& sound() = 0;
    virtual Timer& timer() = 0;
    virtual Keyboard& keyboard() = 0;
};
}
