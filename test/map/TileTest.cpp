#include "map/Tile.h"

#include "util/Exception.h"

#include <gtest/gtest.h>

namespace map {

TEST(TileTest, Creation) {
    const Tile tile1(TileType::E);
    EXPECT_EQ(tile1.type(), TileType::E);
    EXPECT_EQ(tile1.action(), Action::NONE);

    const Tile tile2(TileType::S);
    EXPECT_EQ(tile2.type(), TileType::S);
    EXPECT_EQ(tile2.action(), Action::NONE);

    const Tile tile3(TileType::ROAD, Action::ENEMY_NORTH);
    EXPECT_EQ(tile3.type(), TileType::ROAD);
    EXPECT_EQ(tile3.action(), Action::ENEMY_NORTH);

    const Tile tile4(TileType::ROAD, Action::STONE_1);
    EXPECT_EQ(tile4.type(), TileType::ROAD);
    EXPECT_EQ(tile4.action(), Action::STONE_1);

    for (const auto type : util::EnumIterator<TileType>()) {
        Tile tileA(type);
        EXPECT_EQ(tileA.type(), type);
        EXPECT_EQ(tileA.action(), Action::NONE);
        for (const auto action : util::EnumIterator<Action>()) {
            if (action == Action::NONE || type == TileType::ROAD) {
                Tile tileB(type, action);
                EXPECT_EQ(tileB.type(), type);
                EXPECT_EQ(tileB.action(), action);
            } else {
                EXPECT_THROW(Tile(type, action), util::Exception);
            }
        }
    }
}

TEST(TileTest, Modification) {
    Tile tile(TileType::E);
    EXPECT_EQ(tile.type(), TileType::E);
    EXPECT_EQ(tile.action(), Action::NONE);

    tile.type(TileType::GRASS);
    EXPECT_EQ(tile.type(), TileType::GRASS);
    EXPECT_EQ(tile.action(), Action::NONE);

    tile.type(TileType::ROAD);
    EXPECT_EQ(tile.type(), TileType::ROAD);
    EXPECT_EQ(tile.action(), Action::NONE);

    tile.action(Action::ENEMY_SOUTH);
    EXPECT_EQ(tile.type(), TileType::ROAD);
    EXPECT_EQ(tile.action(), Action::ENEMY_SOUTH);

    tile.type(TileType::BUSH);
    EXPECT_EQ(tile.type(), TileType::BUSH);
    EXPECT_EQ(tile.action(), Action::NONE); // changed this also

    EXPECT_THROW(tile.action(Action::FUEL), util::Exception);
    EXPECT_EQ(tile.type(), TileType::BUSH);
    EXPECT_EQ(tile.action(), Action::NONE);

    tile.action(Action::NONE);
    for (const auto type : util::EnumIterator<TileType>()) {
        tile.type(type);
        EXPECT_EQ(tile.type(), type);
    }
    tile.type(TileType::ROAD);
    for (const auto action : util::EnumIterator<Action>()) {
        tile.action(action);
        EXPECT_EQ(tile.type(), TileType::ROAD);
        EXPECT_EQ(tile.action(), action);
    }

    tile.action(Action::FUEL);
    tile.type(TileType::ROAD);

    EXPECT_EQ(tile.type(), TileType::ROAD);
    EXPECT_EQ(tile.action(), Action::FUEL);

    tile.type(TileType::GRASS);

    for (const auto action : util::EnumIterator<Action>()) {
        if (action == Action::NONE) {
            tile.action(action);
            EXPECT_EQ(tile.type(), TileType::GRASS);
            EXPECT_EQ(tile.action(), Action::NONE);
        } else {
            EXPECT_THROW(tile.action(action), util::Exception);
            EXPECT_EQ(tile.type(), TileType::GRASS);
            EXPECT_EQ(tile.action(), Action::NONE);
        }
    }
}
}
