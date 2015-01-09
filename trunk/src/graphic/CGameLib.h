/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de input/gfx/sfx/misc.
*/

#pragma once

#include <allegro.h>

namespace graphic {

class GameLib {
    public:
        static BITMAP * buffer;

        int Init(unsigned int uiWidth, unsigned int uiHeight);
        void End();
};

}

