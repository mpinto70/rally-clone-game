
#include <string>

namespace tools {

std::string get_error_message();

void throw_file_error(const std::string& filename);

void throw_allegro_error(const std::string& filename);

void hold_while_pressed(const int index);
}
