#pragma once

#include "gamelib/Timer.h"

namespace gamelib {
namespace allegro {

class Timer : public ::gamelib::Timer {
public:
    Timer();
    ~Timer() override;
};
}
}
