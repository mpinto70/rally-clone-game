#include "helpers.h"

#include <allegro5/allegro.h>

#include <cstring>
#include <stdexcept>

namespace tools {

std::string get_error_message() {
    return std::to_string(errno) + " " + std::string(strerror(errno));
}

void throw_file_error(const std::string& filename) {
    const std::string msg = std::string(filename) + " " + get_error_message();
    throw std::runtime_error(msg);
}

void throw_allegro_error(const std::string& filename) {
    throw std::runtime_error(filename);
}

void hold_while_pressed(const int index) {
    ALLEGRO_KEYBOARD_STATE state;
    al_get_keyboard_state(&state);

    while (al_key_down(&state, index)) {
        usleep(1000);
        al_get_keyboard_state(&state);
    }
}
}
