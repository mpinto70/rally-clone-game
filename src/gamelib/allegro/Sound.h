#pragma once

#include "game/Sound.h"

namespace gamelib {
namespace allegro {

class Sound : public ::game::Sound {
public:
    Sound();
    ~Sound() override;
};
}
}
