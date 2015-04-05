
#include "testCTile.h"

#include "map/CTile.h"
#include "util/CException.h"

namespace map {

void testCTile::testCreation() {
    const CTile tile1(ETile::RIGHT);
    TS_ASSERT_EQUALS(tile1.type(), ETile::RIGHT);
    TS_ASSERT_EQUALS(tile1.action(), EAction::NONE);

    const CTile tile2(ETile::BOTTOM);
    TS_ASSERT_EQUALS(tile2.type(), ETile::BOTTOM);
    TS_ASSERT_EQUALS(tile2.action(), EAction::NONE);

    const CTile tile3(ETile::ROAD, EAction::CREATE_ENEMY);
    TS_ASSERT_EQUALS(tile3.type(), ETile::ROAD);
    TS_ASSERT_EQUALS(tile3.action(), EAction::CREATE_ENEMY);

    const CTile tile4(ETile::ROAD, EAction::CREATE_STONE);
    TS_ASSERT_EQUALS(tile4.type(), ETile::ROAD);
    TS_ASSERT_EQUALS(tile4.action(), EAction::CREATE_STONE);

    for (const auto type : util::CEnumIterator<ETile>()) {
        CTile tileA(type);
        TS_ASSERT_EQUALS(tileA.type(), type);
        TS_ASSERT_EQUALS(tileA.action(), EAction::NONE);
        for (const auto action : util::CEnumIterator<EAction>()) {
            if (action == EAction::NONE || type == ETile::ROAD) {
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

