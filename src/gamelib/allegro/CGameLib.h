/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de input/gfx/sfx/misc.
*/

#pragma once

#include "gamelib/IGameLib.h"
#include <allegro.h>

namespace gamelib {
namespace allegro {

class CGameLib : public IGameLib {
    public:
        CGameLib(unsigned int width, unsigned int height);
        virtual ~CGameLib();
    private:
        BITMAP * buffer_;
};

}
}

