/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de input/gfx/sfx/misc.
*/

#pragma once

#include "gamelib/allegro/CGraphic.h"
#include "gamelib/allegro/CKeyboard.h"
#include "gamelib/allegro/CSound.h"
#include "gamelib/allegro/CTimer.h"

#include "gamelib/IGameLib.h"

namespace gamelib {
namespace allegro {

class CGameLib : public IGameLib {
public:
    CGameLib(unsigned int width,
          unsigned int height,
          const std::string& path_to_data);
    ~CGameLib() override;

    CGraphic& graphic() override { return *graphic_; }
    CSound& sound() override { return *sound_; }
    CTimer& timer() override { return *timer_; }
    CKeyboard& keyboard() override { return *keyboard_; }

private:
    CGraphic* graphic_;
    CKeyboard* keyboard_;
    CSound* sound_;
    CTimer* timer_;
};
}
}
