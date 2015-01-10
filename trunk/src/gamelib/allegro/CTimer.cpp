/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de timer.
 */

#include "CTimer.h"
#include "util/CException.h"
#include <allegro.h>

namespace gamelib {
namespace allegro {
CTimer::CTimer() {
    const int allegResult = install_timer();
    if (allegResult != 0)
        throw util::CException("CTimer::CTimer - Error initializing timer", allegResult);
}

CTimer::~CTimer() {
}

}
}

