#pragma once

#include "gamelib/Timer.h"

namespace game {
namespace mck {

class TimerMock : public Timer {
public:
    ~TimerMock() override;
};
}
}
