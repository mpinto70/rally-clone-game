
#include "testCController.h"

#include "../mck/gamelib/CGameLibUtils.h"
#include "../mck/gamelib/CKeyboardMock.h"

#include "game/CController.h"
#include "util/CException.h"

namespace game {

std::string getRallyDir() {
    const char * home = getenv("HOME");
    if (home == nullptr) {
        throw util::CException("Environment variable HOME not set", 1);
    }

    return std::string(home) + "/.rallyX";
}

void testCController::testCreation() {
    auto gameLib = gamelib::mck::CGameLibUtils::createDefault();
    TS_ASSERT(gameLib.get() != nullptr);

    CController cont(gameLib, getRallyDir(), 15);
    gamelib::mck::CKeyboardMock::add(gamelib::EKey::ESCAPE);
    cont.run();
}

void testCController::testInvalidCreation() {
    std::unique_ptr<gamelib::IGameLib> empty;
    TS_ASSERT_THROWS_EQUALS(CController c(empty, "some_path", 13),
                            util::CException & e,
                            std::string(e.what()),
                            "CController - game lib was null");
}

}

