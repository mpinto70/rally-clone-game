#include "../mck/game/GameLibUtils.h"
#include "../mck/game/KeyboardMock.h"

#include "game/Controller.h"

#include "util/Exception.h"

#include <gtest/gtest.h>

namespace game {

std::string getRallyDir() {
    return RALLY_ROOT "/test/game/files";
}

TEST(ControllerTest, Creation) {
    auto gameLib = game::mck::GameLibUtils::createDefault();
    EXPECT_TRUE(gameLib.get() != nullptr);

    Controller cont(gameLib, getRallyDir(), 15);
    game::mck::KeyboardMock::add(game::Key::ESCAPE);
    cont.run();
}

TEST(ControllerTest, InvalidCreation) {
    std::unique_ptr<game::GameLib> empty;
    EXPECT_THROW(Controller c(empty, "some_path", 13), util::Exception);
}
}
