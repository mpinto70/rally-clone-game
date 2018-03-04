/**
 Rally-X Clone - 2015
 main code.
 */

#include "game/CController.h"
#include "gamelib/allegro/CGameLib.h"
#include "util/CException.h"

#include <iostream>
#include <memory>

// Essas duas constantes ficam por aqui mesmo?
static const unsigned int UTIL_W = 640, UTIL_H = 480;

std::string getRallyDir() {
    const char* home = getenv("HOME");
    if (home == nullptr) {
        throw util::CException("Environment variable HOME not set", 1);
    }

    return std::string(home) + "/.rallyX";
}

int main() {
    using gamelib::IGameLib;
    using gamelib::allegro::CGameLib;
    try {
        const auto rallyDir = getRallyDir();
        std::unique_ptr<IGameLib> gameLib(new CGameLib(UTIL_W, UTIL_H, rallyDir));
        game::CController controller(gameLib, rallyDir, 15);
        controller.run();
        return 0;
    } catch (const util::CException& e) {
        std::cout << "An ERROR occurred" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "Code: " << e.code() << std::endl;
        return 1;
    }
}
END_OF_MAIN()
