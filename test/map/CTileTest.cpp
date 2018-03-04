#include "map/CTile.h"
#include "util/CException.h"

#include <gtest/gtest.h>

namespace map {

TEST(CTileTest, Creation) {
    const CTile tile1(ETileType::RIGHT);
    EXPECT_EQ(tile1.type(), ETileType::RIGHT);
    EXPECT_EQ(tile1.action(), EAction::NONE);

    const CTile tile2(ETileType::BOTTOM);
    EXPECT_EQ(tile2.type(), ETileType::BOTTOM);
    EXPECT_EQ(tile2.action(), EAction::NONE);

    const CTile tile3(ETileType::ROAD, EAction::ENEMY_NORTH);
    EXPECT_EQ(tile3.type(), ETileType::ROAD);
    EXPECT_EQ(tile3.action(), EAction::ENEMY_NORTH);

    const CTile tile4(ETileType::ROAD, EAction::STONE);
    EXPECT_EQ(tile4.type(), ETileType::ROAD);
    EXPECT_EQ(tile4.action(), EAction::STONE);

    for (const auto type : util::CEnumIterator<ETileType>()) {
        CTile tileA(type);
        EXPECT_EQ(tileA.type(), type);
        EXPECT_EQ(tileA.action(), EAction::NONE);
        for (const auto action : util::CEnumIterator<EAction>()) {
            if (action == EAction::NONE || type == ETileType::ROAD) {
                CTile tileB(type, action);
                EXPECT_EQ(tileB.type(), type);
                EXPECT_EQ(tileB.action(), action);
            } else {
                EXPECT_THROW(CTile(type, action), util::CException);
            }
        }
    }
}

TEST(CTileTest, Modification) {
    CTile tile(ETileType::RIGHT);
    EXPECT_EQ(tile.type(), ETileType::RIGHT);
    EXPECT_EQ(tile.action(), EAction::NONE);

    tile.type(ETileType::GRASS);
    EXPECT_EQ(tile.type(), ETileType::GRASS);
    EXPECT_EQ(tile.action(), EAction::NONE);

    tile.type(ETileType::ROAD);
    EXPECT_EQ(tile.type(), ETileType::ROAD);
    EXPECT_EQ(tile.action(), EAction::NONE);

    tile.action(EAction::ENEMY_SOUTH);
    EXPECT_EQ(tile.type(), ETileType::ROAD);
    EXPECT_EQ(tile.action(), EAction::ENEMY_SOUTH);

    tile.type(ETileType::BUSH);
    EXPECT_EQ(tile.type(), ETileType::BUSH);
    EXPECT_EQ(tile.action(), EAction::NONE); // changed this also

    EXPECT_THROW(tile.action(EAction::FUEL), util::CException);
    EXPECT_EQ(tile.type(), ETileType::BUSH);
    EXPECT_EQ(tile.action(), EAction::NONE);

    tile.action(EAction::NONE);
    for (const auto type : util::CEnumIterator<ETileType>()) {
        tile.type(type);
        EXPECT_EQ(tile.type(), type);
    }
    tile.type(ETileType::ROAD);
    for (const auto action : util::CEnumIterator<EAction>()) {
        tile.action(action);
        EXPECT_EQ(tile.type(), ETileType::ROAD);
        EXPECT_EQ(tile.action(), action);
    }

    tile.action(EAction::FUEL);
    tile.type(ETileType::ROAD);

    EXPECT_EQ(tile.type(), ETileType::ROAD);
    EXPECT_EQ(tile.action(), EAction::FUEL);

    tile.type(ETileType::GRASS);

    for (const auto action : util::CEnumIterator<EAction>()) {
        if (action == EAction::NONE) {
            tile.action(action);
            EXPECT_EQ(tile.type(), ETileType::GRASS);
            EXPECT_EQ(tile.action(), EAction::NONE);
        } else {
            EXPECT_THROW(tile.action(action), util::CException);
            EXPECT_EQ(tile.type(), ETileType::GRASS);
            EXPECT_EQ(tile.action(), EAction::NONE);
        }
    }
}
}
