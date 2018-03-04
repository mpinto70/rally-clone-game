#include "map/EAction.h"
#include "util/CException.h"

#include <gtest/gtest.h>

namespace map {

TEST(EActionTest, ToString) {
    EXPECT_EQ(to_string(EAction::NONE), "EAction::NONE");
    EXPECT_EQ(to_string(EAction::FUEL), "EAction::FUEL");
    EXPECT_EQ(to_string(EAction::ENEMY_NORTH), "EAction::ENEMY_NORTH");
    EXPECT_EQ(to_string(EAction::ENEMY_WEST), "EAction::ENEMY_WEST");
    EXPECT_EQ(to_string(EAction::ENEMY_SOUTH), "EAction::ENEMY_SOUTH");
    EXPECT_EQ(to_string(EAction::ENEMY_EAST), "EAction::ENEMY_EAST");
    EXPECT_EQ(to_string(EAction::STONE), "EAction::STONE");

    EXPECT_THROW(to_string(EAction::LAST), util::CException);

    for (const auto tile : util::CEnumIterator<EAction>()) {
        EXPECT_NO_THROW(to_string(tile));
    }
}
}
