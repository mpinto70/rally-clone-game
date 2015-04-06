
#include "testCMap.h"

#include "map/CMap.h"

namespace map {

void testCMap::testCreation() {
    std::vector<CTile> tiles = {
        CTile{ ETile::ROAD, EAction::CREATE_STONE },
        CTile{ ETile::BUSH, EAction::NONE }
    };

    const CMap m1(1, 2, tiles);
    TS_ASSERT_EQUALS(m1.width(), 1u);
    TS_ASSERT_EQUALS(m1.height(), 2u);
    TS_ASSERT_EQUALS(m1.tiles(), tiles);

    tiles = {
        CTile{ ETile::ROAD,      EAction::CREATE_ENEMY },
        CTile{ ETile::BUSH,      EAction::NONE },
        CTile{ ETile::BOTTOM,    EAction::NONE },
        CTile{ ETile::GRASS,     EAction::NONE },
        CTile{ ETile::LEFT,      EAction::NONE },
        CTile{ ETile::RIGHT,     EAction::NONE }
    };

    const CMap m2(2, 3, tiles);
    TS_ASSERT_EQUALS(m2.width(), 2u);
    TS_ASSERT_EQUALS(m2.height(), 3u);
    TS_ASSERT_EQUALS(m2.tiles(), tiles);
}

void testCMap::testInvalidCreation() {
    TS_ASSERT_THROWS_EQUALS(CMap(0, 2, { CTile{ ETile::ROAD, EAction::CREATE_STONE } , CTile{ ETile::BUSH, EAction::NONE} }),
    std::invalid_argument & e,
    std::string(e.what()),
    "CMap - zero width");

    TS_ASSERT_THROWS_EQUALS(CMap(1, 0, { CTile{ ETile::ROAD, EAction::CREATE_STONE } , CTile{ ETile::BUSH, EAction::NONE} }),
    std::invalid_argument & e,
    std::string(e.what()),
    "CMap - zero height");

    TS_ASSERT_THROWS_EQUALS(CMap(1, 3, { CTile{ ETile::ROAD, EAction::CREATE_STONE } , CTile{ ETile::BUSH, EAction::NONE} }),
    std::invalid_argument & e,
    std::string(e.what()),
    "CMap - number of tiles (2) is not compatible with width X height (1 X 3)");
}

}

