/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de gfx.
*/

#pragma once

#include "gamelib/IGraphic.h"
#include <allegro.h>

namespace gamelib {
namespace allegro {

class CGraphic : public IGraphic {
    public:
        CGraphic(unsigned int width, unsigned int height);
        ~CGraphic() override;
    private:
        BITMAP * buffer_;
};

}
}

