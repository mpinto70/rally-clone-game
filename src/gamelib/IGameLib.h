
#pragma once

#include "gamelib/IGraphic.h"
#include "gamelib/IKeyboard.h"
#include "gamelib/ISound.h"
#include "gamelib/ITimer.h"

namespace gamelib {

class IGameLib {
public:
    virtual ~IGameLib() = 0;
    virtual IGraphic& graphic() = 0;
    virtual ISound& sound() = 0;
    virtual ITimer& timer() = 0;
    virtual IKeyboard& keyboard() = 0;
};
}
