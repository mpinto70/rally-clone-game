#pragma once

#include "gamelib/Sound.h"

namespace game {
namespace mck {

class SoundMock : public Sound {
public:
    ~SoundMock() override;
};
}
}
