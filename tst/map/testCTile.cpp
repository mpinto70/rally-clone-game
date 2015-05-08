
#include "testCTile.h"

#include "map/CTile.h"
#include "util/CException.h"

namespace map {

void testCTile::testCreation() {
    const CTile tile1(ETileType::RIGHT);
    TS_ASSERT_EQUALS(tile1.type(), ETileType::RIGHT);
    TS_ASSERT_EQUALS(tile1.action(), EAction::NONE);

    const CTile tile2(ETileType::BOTTOM);
    TS_ASSERT_EQUALS(tile2.type(), ETileType::BOTTOM);
    TS_ASSERT_EQUALS(tile2.action(), EAction::NONE);

    const CTile tile3(ETileType::ROAD, EAction::ENEMY_NORTH);
    TS_ASSERT_EQUALS(tile3.type(), ETileType::ROAD);
    TS_ASSERT_EQUALS(tile3.action(), EAction::ENEMY_NORTH);

    const CTile tile4(ETileType::ROAD, EAction::STONE);
    TS_ASSERT_EQUALS(tile4.type(), ETileType::ROAD);
    TS_ASSERT_EQUALS(tile4.action(), EAction::STONE);

    for (const auto type : util::CEnumIterator<ETileType>()) {
        CTile tileA(type);
        TS_ASSERT_EQUALS(tileA.type(), type);
        TS_ASSERT_EQUALS(tileA.action(), EAction::NONE);
        for (const auto action : util::CEnumIterator<EAction>()) {
            if (action == EAction::NONE || type == ETileType::ROAD) {
                CTile tileB(type, action);
                TS_ASSERT_EQUALS(tileB.type(), type);
                TS_ASSERT_EQUALS(tileB.action(), action);
            } else {
                TS_ASSERT_THROWS(CTile(type, action),
                                 util::CException);
            }
        }
    }
}

void testCTile::testModification() {
    CTile tile(ETileType::RIGHT);
    TS_ASSERT_EQUALS(tile.type(), ETileType::RIGHT);
    TS_ASSERT_EQUALS(tile.action(), EAction::NONE);

    tile.type(ETileType::GRASS);
    TS_ASSERT_EQUALS(tile.type(), ETileType::GRASS);
    TS_ASSERT_EQUALS(tile.action(), EAction::NONE);

    tile.type(ETileType::ROAD);
    TS_ASSERT_EQUALS(tile.type(), ETileType::ROAD);
    TS_ASSERT_EQUALS(tile.action(), EAction::NONE);

    tile.action(EAction::ENEMY_SOUTH);
    TS_ASSERT_EQUALS(tile.type(), ETileType::ROAD);
    TS_ASSERT_EQUALS(tile.action(), EAction::ENEMY_SOUTH);

    tile.type(ETileType::BUSH);
    TS_ASSERT_EQUALS(tile.type(), ETileType::BUSH);
    TS_ASSERT_EQUALS(tile.action(), EAction::NONE); // changed this also

    TS_ASSERT_THROWS(tile.action(EAction::FUEL), util::CException);
    TS_ASSERT_EQUALS(tile.type(), ETileType::BUSH);
    TS_ASSERT_EQUALS(tile.action(), EAction::NONE);

    tile.action(EAction::NONE);
    for (const auto type : util::CEnumIterator<ETileType>()) {
        tile.type(type);
        TS_ASSERT_EQUALS(tile.type(), type);
    }
    tile.type(ETileType::ROAD);
    for (const auto action : util::CEnumIterator<EAction>()) {
        tile.action(action);
        TS_ASSERT_EQUALS(tile.type(), ETileType::ROAD);
        TS_ASSERT_EQUALS(tile.action(), action);
    }

    tile.action(EAction::FUEL);
    tile.type(ETileType::ROAD);

    TS_ASSERT_EQUALS(tile.type(), ETileType::ROAD);
    TS_ASSERT_EQUALS(tile.action(), EAction::FUEL);

    tile.type(ETileType::GRASS);

    for (const auto action : util::CEnumIterator<EAction>()) {
        if (action == EAction::NONE) {
            tile.action(action);
            TS_ASSERT_EQUALS(tile.type(), ETileType::GRASS);
            TS_ASSERT_EQUALS(tile.action(), EAction::NONE);
        } else {
            TS_ASSERT_THROWS(tile.action(action), util::CException);
            TS_ASSERT_EQUALS(tile.type(), ETileType::GRASS);
            TS_ASSERT_EQUALS(tile.action(), EAction::NONE);
        }
    }
}

}

