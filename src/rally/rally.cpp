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

std::string getRallyDir() {
    const char * home = getenv("HOME");
    if (home == nullptr) {
        throw util::CException("Environment variable HOME not set", 1);
    }

    return std::string(home) + "/.rallyX";
}

int main() {
    using gamelib::allegro::CGameLib;
    using gamelib::IGameLib;
    try {
        util::CSingleton<IGameLib>::create(std::unique_ptr<CGameLib>(new CGameLib(UTIL_W, UTIL_H, getRallyDir())));
        // put the game here
        util::CSingleton<IGameLib>::destroy();
        return 0;
    } catch (const util::CException & e) {
        util::CSingleton<IGameLib>::destroy();
        std::cout << "An ERROR occurred" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "Code: " << e.code() << std::endl;
        return 1;
    }
}
END_OF_MAIN()

