#include "game/Controller.h"
#include "gamelib/allegro/GameLib.h"
#include "util/Exception.h"

#include <iostream>
#include <memory>

namespace {
    constexpr unsigned int UTIL_W = 640, UTIL_H = 480;
}

std::string getRallyDir() {
    const char* home = getenv("HOME");
    if (home == nullptr) {
        throw util::Exception("Environment variable HOME not set", 1);
    }

    return std::string(home) + "/.rallyX";
}

int main() {
    using gamelib::allegro::GameLib;
    try {
        const auto rallyDir = getRallyDir();
        std::unique_ptr<game::GameLib> gameLib(new GameLib(rallyDir, UTIL_W, UTIL_H));
        game::Controller controller(gameLib, rallyDir, 15);
        controller.run();
        return 0;
    } catch (const util::Exception& e) {
        std::cout << "An ERROR occurred" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "Code: " << e.code() << std::endl;
        return 1;
    }
}
