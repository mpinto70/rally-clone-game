
#include "helpers.h"

#include <allegro.h>

#include <stdexcept>
#include <string.h>

namespace tools {

std::string get_error_message() {
    return std::to_string(errno) + " " + std::string(strerror(errno));
}

void throw_file_error(const std::string& filename) {
    const std::string msg = std::string(filename) + " " + get_error_message();
    throw std::runtime_error(msg);
}

void throw_allegro_error(const std::string& filename) {
    const std::string msg = std::string(filename) + " " + allegro_error;
    throw std::runtime_error(msg);
}

void hold_while_pressed(const int index) {
    while (key[index])
        usleep(1000);
}
}
