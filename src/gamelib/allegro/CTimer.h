/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de timer.
*/

#pragma once

#include "gamelib/ITimer.h"

namespace gamelib {
namespace allegro {

class CTimer : public ITimer {
public:
    CTimer();
    ~CTimer() override;
};

}
}

