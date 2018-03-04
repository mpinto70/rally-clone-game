#include "game/Controller.h"
#include "util/Exception.h"

#include "../mck/gamelib/GameLibUtils.h"
#include "../mck/gamelib/KeyboardMock.h"

#include <gtest/gtest.h>

namespace game {

std::string getRallyDir() {
    return RALLY_ROOT "/test/game/files";
}

TEST(ControllerTest, Creation) {
    auto gameLib = gamelib::mck::GameLibUtils::createDefault();
    EXPECT_TRUE(gameLib.get() != nullptr);

    Controller cont(gameLib, getRallyDir(), 15);
    gamelib::mck::KeyboardMock::add(gamelib::Key::ESCAPE);
    cont.run();
}

TEST(ControllerTest, InvalidCreation) {
    std::unique_ptr<gamelib::GameLib> empty;
    EXPECT_THROW(Controller c(empty, "some_path", 13),
          util::Exception);
}
}
