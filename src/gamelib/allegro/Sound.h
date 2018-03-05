#pragma once

#include "gamelib/Sound.h"

namespace gamelib {
namespace allegro {

class Sound : public ::gamelib::Sound {
public:
    Sound();
    ~Sound() override;
};
}
}
