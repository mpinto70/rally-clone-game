#pragma once

#include "gamelib/Sound.h"

namespace gamelib {
namespace mck {

class SoundMock : public Sound {
public:
    ~SoundMock() override;
};
}
}
