#include "Sound.h"

#include "util/Exception.h"

#include <allegro.h>

namespace gamelib {
namespace allegro {

Sound::Sound() {
    /* no sound for now
    const int allegResult = install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, nullptr);

    if (allegResult != 0)
        throw util::Exception("Sound::Sound - Error initializing sound", allegResult);
    */
}

Sound::~Sound() = default;
}
}
