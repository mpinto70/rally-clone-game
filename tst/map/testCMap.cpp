
#include "testCMap.h"

#include "map/CMap.h"

namespace map {

void TestCMap::testCreation() {
    std::vector<ETile> tiles = { ETile::ROAD, ETile::BUSH };

    const CMap m1(1, 2, tiles);
    TS_ASSERT_EQUALS(m1.width(), 1u);
    TS_ASSERT_EQUALS(m1.height(), 2u);
    TS_ASSERT_EQUALS(m1.tiles(), tiles);

    tiles = {
        ETile::ROAD, ETile::BUSH,
        ETile::BOTTOM, ETile::GRASS,
        ETile::LEFT, ETile::RIGHT
    };

    const CMap m2(2, 3, tiles);
    TS_ASSERT_EQUALS(m2.width(), 2u);
    TS_ASSERT_EQUALS(m2.height(), 3u);
    TS_ASSERT_EQUALS(m2.tiles(), tiles);
}

void TestCMap::testInvalidCreation() {
    TS_ASSERT_THROWS_EQUALS(CMap(0, 2, { ETile::ROAD, ETile::BUSH }),
                            std::invalid_argument & e,
                            std::string(e.what()),
                            "CMap - zero width");

    TS_ASSERT_THROWS_EQUALS(CMap(1, 0, { ETile::ROAD, ETile::BUSH }),
                            std::invalid_argument & e,
                            std::string(e.what()),
                            "CMap - zero height");

    TS_ASSERT_THROWS_EQUALS(CMap(1, 3, { ETile::ROAD, ETile::BUSH }),
                            std::invalid_argument & e,
                            std::string(e.what()),
                            "CMap - number of tiles (2) is not compatible with width X height (1 X 3)");
}

}

