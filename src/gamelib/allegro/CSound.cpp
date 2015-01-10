/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de sfx.
 */

#include "CSound.h"
#include "util/CException.h"
#include <allegro.h>

namespace gamelib {
namespace allegro {

CSound::CSound() {
    /* no sound for now
    const int allegResult = install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, nullptr);

    if (allegResult != 0)
        throw util::CException("CSound::CSound - Error initializing sound", allegResult);
    */
}

CSound::~CSound() {
}

}
}

