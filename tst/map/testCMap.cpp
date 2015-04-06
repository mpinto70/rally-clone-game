
#include "testCMap.h"

#include "map/CMap.h"
#include "util/CException.h"

namespace map {

void testCMap::testCreation() {
    std::vector<CTile> tiles = {
        CTile{ ETileType::ROAD, EAction::STONE },
        CTile{ ETileType::BUSH, EAction::NONE }
    };

    const CMap m1(1, 2, tiles);
    TS_ASSERT_EQUALS(m1.width(), 1u);
    TS_ASSERT_EQUALS(m1.height(), 2u);
    TS_ASSERT_EQUALS(m1.tiles(), tiles);

    tiles = {
        CTile{ ETileType::ROAD,      EAction::ENEMY_UP },
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
    TS_ASSERT_THROWS_EQUALS(CMap(0, 2, { CTile{ ETileType::ROAD, EAction::STONE } , CTile{ ETileType::BUSH, EAction::NONE} }),
                            std::invalid_argument & e,
                            std::string(e.what()),
                            "CMap - zero width");

    TS_ASSERT_THROWS_EQUALS(CMap(1, 0, { CTile{ ETileType::ROAD, EAction::STONE } , CTile{ ETileType::BUSH, EAction::NONE} }),
                            std::invalid_argument & e,
                            std::string(e.what()),
                            "CMap - zero height");

    TS_ASSERT_THROWS_EQUALS(CMap(1, 3, { CTile{ ETileType::ROAD, EAction::STONE } , CTile{ ETileType::BUSH, EAction::NONE} }),
                            std::invalid_argument & e,
                            std::string(e.what()),
                            "CMap - number of tiles (2) is not compatible with width X height (1 X 3)");
}

void testCMap::testIndexing() {
    std::vector<CTile> tiles = {
        CTile{ ETileType::ROAD, EAction::STONE },
        CTile{ ETileType::BUSH, EAction::NONE }
    };

    const CMap m1(1, 2, tiles);
    TS_ASSERT_EQUALS(m1(0, 0), CTile(ETileType::ROAD, EAction::STONE));
    TS_ASSERT_EQUALS(m1(0, 1), CTile(ETileType::BUSH, EAction::NONE));
    TS_ASSERT_THROWS_EQUALS(m1(1, 0),
                            util::CException & e,
                            std::string(e.what()),
                            "CMap() - horizontal coordinate out of range");
    TS_ASSERT_THROWS_EQUALS(m1(0, 2),
                            util::CException & e,
                            std::string(e.what()),
                            "CMap() - vertical coordinate out of range");

    const CMap m2(2, 1, tiles);
    TS_ASSERT_EQUALS(m2(0, 0), CTile(ETileType::ROAD, EAction::STONE));
    TS_ASSERT_EQUALS(m2(1, 0), CTile(ETileType::BUSH, EAction::NONE));
    TS_ASSERT_THROWS_EQUALS(m2(2, 0),
                            util::CException & e,
                            std::string(e.what()),
                            "CMap() - horizontal coordinate out of range");
    TS_ASSERT_THROWS_EQUALS(m2(0, 1),
                            util::CException & e,
                            std::string(e.what()),
                            "CMap() - vertical coordinate out of range");


    tiles = {
        CTile{ ETileType::ROAD,      EAction::ENEMY_UP },
        CTile{ ETileType::BUSH,      EAction::NONE },
        CTile{ ETileType::BOTTOM,    EAction::NONE },
        CTile{ ETileType::GRASS,     EAction::NONE },
        CTile{ ETileType::LEFT,      EAction::NONE },
        CTile{ ETileType::RIGHT,     EAction::NONE }
    };

    const CMap m3(2, 3, tiles);
    TS_ASSERT_EQUALS(m3(0, 0), CTile(ETileType::ROAD,      EAction::ENEMY_UP));
    TS_ASSERT_EQUALS(m3(1, 0), CTile(ETileType::BUSH,      EAction::NONE));
    TS_ASSERT_EQUALS(m3(0, 1), CTile(ETileType::BOTTOM,    EAction::NONE));
    TS_ASSERT_EQUALS(m3(1, 1), CTile(ETileType::GRASS,     EAction::NONE));
    TS_ASSERT_EQUALS(m3(0, 2), CTile(ETileType::LEFT,      EAction::NONE));
    TS_ASSERT_EQUALS(m3(1, 2), CTile(ETileType::RIGHT,     EAction::NONE));

    TS_ASSERT_THROWS_EQUALS(m3(2, 0),
                            util::CException & e,
                            std::string(e.what()),
                            "CMap() - horizontal coordinate out of range");
    TS_ASSERT_THROWS_EQUALS(m3(0, 3),
                            util::CException & e,
                            std::string(e.what()),
                            "CMap() - vertical coordinate out of range");

    const CMap m4(3, 2, tiles);
    TS_ASSERT_EQUALS(m4(0, 0), CTile(ETileType::ROAD,      EAction::ENEMY_UP));
    TS_ASSERT_EQUALS(m4(1, 0), CTile(ETileType::BUSH,      EAction::NONE));
    TS_ASSERT_EQUALS(m4(2, 0), CTile(ETileType::BOTTOM,    EAction::NONE));
    TS_ASSERT_EQUALS(m4(0, 1), CTile(ETileType::GRASS,     EAction::NONE));
    TS_ASSERT_EQUALS(m4(1, 1), CTile(ETileType::LEFT,      EAction::NONE));
    TS_ASSERT_EQUALS(m4(2, 1), CTile(ETileType::RIGHT,     EAction::NONE));

    TS_ASSERT_THROWS_EQUALS(m4(3, 0),
                            util::CException & e,
                            std::string(e.what()),
                            "CMap() - horizontal coordinate out of range");
    TS_ASSERT_THROWS_EQUALS(m4(0, 2),
                            util::CException & e,
                            std::string(e.what()),
                            "CMap() - vertical coordinate out of range");
}

}

