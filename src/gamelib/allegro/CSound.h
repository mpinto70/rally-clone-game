/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de sfx.
*/

#pragma once

#include "gamelib/ISound.h"

namespace gamelib {
namespace allegro {

class CSound : public ISound {
public:
    CSound();
    ~CSound() override;
};

}
}

