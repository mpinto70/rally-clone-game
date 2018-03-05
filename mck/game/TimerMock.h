#pragma once

#include "game/Timer.h"

namespace game {
namespace mck {

class TimerMock : public Timer {
public:
    ~TimerMock() override;
};
}
}
