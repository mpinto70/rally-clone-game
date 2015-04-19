
#include "testCController.h"

#include "../mck/gamelib/CGameLibUtils.h"
#include "../mck/gamelib/CKeyboardMock.h"

#include "game/CController.h"
#include "util/CException.h"

namespace game {

void testCController::testCreation() {
    auto gameLib = gamelib::mck::CGameLibUtils::createDefault();
    TS_ASSERT(gameLib.get() != nullptr);

    CController cont(gameLib);
    gamelib::mck::CKeyboardMock::add(gamelib::KEYS::ESCAPE);
    cont.run();
}

void testCController::testInvalidCreation() {
    std::unique_ptr<gamelib::IGameLib> empty;
    TS_ASSERT_THROWS_EQUALS(CController c(empty),
                            util::CException & e,
                            std::string(e.what()),
                            "CController - game lib was null");
}

}

