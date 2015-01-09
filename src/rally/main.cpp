/**
 Rally-X Clone - 2015
 main code.
 */

#include "graphic/CGameLib.h"
#include "util/CException.h"

#include <iostream>

// Essas duas constantes ficam por aqui mesmo?
static const unsigned int UTIL_W = 480, UTIL_H = 240;

int main() {
    try {
        graphic::GameLib gameLib(UTIL_W, UTIL_H);
        return 0;
    } catch (const util::CException & e) {
        std::cout << "An ERROR occurred" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "Code: " << e.code() << std::endl;
        return 1;
    }
}
END_OF_MAIN()

