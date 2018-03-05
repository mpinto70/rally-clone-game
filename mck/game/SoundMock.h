#pragma once

#include "game/Sound.h"

namespace game {
namespace mck {

class SoundMock : public Sound {
public:
    ~SoundMock() override;
};
}
}
