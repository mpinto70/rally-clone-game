#pragma once

#include "game/Timer.h"

namespace gamelib {
namespace allegro {

class Timer : public ::game::Timer {
public:
    Timer();
    ~Timer() override;
};
}
}
