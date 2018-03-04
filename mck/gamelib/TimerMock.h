#pragma once

#include "gamelib/Timer.h"

namespace gamelib {
namespace mck {

class TimerMock : public Timer {
    public:
        ~TimerMock() override;
};

}
}
