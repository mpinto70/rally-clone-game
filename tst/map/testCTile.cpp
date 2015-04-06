
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

    const CTile tile3(ETileType::ROAD, EAction::CREATE_ENEMY);
    TS_ASSERT_EQUALS(tile3.type(), ETileType::ROAD);
    TS_ASSERT_EQUALS(tile3.action(), EAction::CREATE_ENEMY);

    const CTile tile4(ETileType::ROAD, EAction::CREATE_STONE);
    TS_ASSERT_EQUALS(tile4.type(), ETileType::ROAD);
    TS_ASSERT_EQUALS(tile4.action(), EAction::CREATE_STONE);

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

}

