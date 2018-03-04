#include "../mck/gamelib/CGameLibUtils.h"
#include "../mck/gamelib/CKeyboardMock.h"

#include "game/CController.h"
#include "util/CException.h"

#include <gtest/gtest.h>

namespace game {

std::string getRallyDir() {
    return RALLY_ROOT "/test/game/files";
}

TEST(CControllerTest, Creation) {
    auto gameLib = gamelib::mck::CGameLibUtils::createDefault();
    EXPECT_TRUE(gameLib.get() != nullptr);

    CController cont(gameLib, getRallyDir(), 15);
    gamelib::mck::CKeyboardMock::add(gamelib::EKey::ESCAPE);
    cont.run();
}

TEST(CControllerTest, InvalidCreation) {
    std::unique_ptr<gamelib::IGameLib> empty;
    EXPECT_THROW(CController c(empty, "some_path", 13),
          util::CException);
}
}
