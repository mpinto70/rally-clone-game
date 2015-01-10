/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de input/gfx/sfx/misc.
*/

#pragma once

#include <allegro.h>

namespace gamelib {

class GameLib {
    public:
        GameLib(unsigned int width, unsigned int height);
        ~GameLib();
    private:
        BITMAP * buffer_;
};

}

