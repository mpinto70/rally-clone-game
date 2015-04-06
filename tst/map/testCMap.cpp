
#include "testCMap.h"

#include "map/CMap.h"

namespace map {

void testCMap::testCreation() {
    std::vector<CTile> tiles = {
        CTile{ ETileType::ROAD, EAction::CREATE_STONE },
        CTile{ ETileType::BUSH, EAction::NONE }
    };

    const CMap m1(1, 2, tiles);
    TS_ASSERT_EQUALS(m1.width(), 1u);
    TS_ASSERT_EQUALS(m1.height(), 2u);
    TS_ASSERT_EQUALS(m1.tiles(), tiles);

    tiles = {
        CTile{ ETileType::ROAD,      EAction::CREATE_ENEMY },
        CTile{ ETileType::BUSH,      EAction::NONE },
        CTile{ ETileType::BOTTOM,    EAction::NONE },
        CTile{ ETileType::GRASS,     EAction::NONE },
        CTile{ ETileType::LEFT,      EAction::NONE },
        CTile{ ETileType::RIGHT,     EAction::NONE }
    };

    const CMap m2(2, 3, tiles);
    TS_ASSERT_EQUALS(m2.width(), 2u);
    TS_ASSERT_EQUALS(m2.height(), 3u);
    TS_ASSERT_EQUALS(m2.tiles(), tiles);
}

void testCMap::testInvalidCreation() {
    TS_ASSERT_THROWS_EQUALS(CMap(0, 2, { CTile{ ETileType::ROAD, EAction::CREATE_STONE } , CTile{ ETileType::BUSH, EAction::NONE} }),
                            std::invalid_argument & e,
                            std::string(e.what()),
                            "CMap - zero width");

    TS_ASSERT_THROWS_EQUALS(CMap(1, 0, { CTile{ ETileType::ROAD, EAction::CREATE_STONE } , CTile{ ETileType::BUSH, EAction::NONE} }),
                            std::invalid_argument & e,
                            std::string(e.what()),
                            "CMap - zero height");

    TS_ASSERT_THROWS_EQUALS(CMap(1, 3, { CTile{ ETileType::ROAD, EAction::CREATE_STONE } , CTile{ ETileType::BUSH, EAction::NONE} }),
                            std::invalid_argument & e,
                            std::string(e.what()),
                            "CMap - number of tiles (2) is not compatible with width X height (1 X 3)");
}

}

