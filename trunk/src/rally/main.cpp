/**
 Rally-X Clone - 2015
 main code.
 */

#include "gamelib/allegro/CGameLib.h"
#include "util/CSingleton.h"
#include "util/CException.h"

#include <iostream>
#include <memory>

// Essas duas constantes ficam por aqui mesmo?
static const unsigned int UTIL_W = 480, UTIL_H = 240;

int main() {
    using gamelib::allegro::CGameLib;
    using gamelib::IGameLib;
    try {
        util::CSingleton<IGameLib>::create(std::unique_ptr<CGameLib>(new CGameLib(UTIL_W, UTIL_H)));
        // put the game here
        util::CSingleton<IGameLib>::destroy();
        return 0;
    } catch (const util::CException & e) {
        std::cout << "An ERROR occurred" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "Code: " << e.code() << std::endl;
        return 1;
    }
}
END_OF_MAIN()

