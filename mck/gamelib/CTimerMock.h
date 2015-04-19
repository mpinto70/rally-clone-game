
#pragma once

#include "gamelib/ITimer.h"

namespace gamelib {
namespace mck {

class CTimerMock : public ITimer {
    public:
        ~CTimerMock() override;
};

}
}
