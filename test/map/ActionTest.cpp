#include "map/Action.h"
#include "util/Exception.h"

#include <gtest/gtest.h>

namespace map {

TEST(ActionTest, ToString) {
    EXPECT_EQ(to_string(Action::NONE), "Action::NONE");
    EXPECT_EQ(to_string(Action::FUEL), "Action::FUEL");
    EXPECT_EQ(to_string(Action::ENEMY_NORTH), "Action::ENEMY_NORTH");
    EXPECT_EQ(to_string(Action::ENEMY_WEST), "Action::ENEMY_WEST");
    EXPECT_EQ(to_string(Action::ENEMY_SOUTH), "Action::ENEMY_SOUTH");
    EXPECT_EQ(to_string(Action::ENEMY_EAST), "Action::ENEMY_EAST");
    EXPECT_EQ(to_string(Action::STONE), "Action::STONE");

    EXPECT_THROW(to_string(Action::LAST), util::Exception);

    for (const auto tile : util::CEnumIterator<Action>()) {
        EXPECT_NO_THROW(to_string(tile));
    }
}
}
