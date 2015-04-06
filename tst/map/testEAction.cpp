
#include "testEAction.h"

#include "map/EAction.h"
#include "util/CException.h"

namespace map {

void testEAction::testToString() {
    TS_ASSERT_EQUALS(to_string(EAction::NONE),          "EAction::NONE");
    TS_ASSERT_EQUALS(to_string(EAction::FUEL),          "EAction::FUEL");
    TS_ASSERT_EQUALS(to_string(EAction::ENEMY_UP),      "EAction::ENEMY_UP");
    TS_ASSERT_EQUALS(to_string(EAction::ENEMY_RIGHT),   "EAction::ENEMY_RIGHT");
    TS_ASSERT_EQUALS(to_string(EAction::ENEMY_DOWN),    "EAction::ENEMY_DOWN");
    TS_ASSERT_EQUALS(to_string(EAction::ENEMY_LEFT),    "EAction::ENEMY_LEFT");
    TS_ASSERT_EQUALS(to_string(EAction::STONE),         "EAction::STONE");

    TS_ASSERT_THROWS_EQUALS(to_string(EAction::LAST),
                            util::CException & e,
                            std::string(e.what()),
                            "to_string(EAction) - invalid argument");

    for (const auto tile : util::CEnumIterator<EAction>()) {
        TS_ASSERT_THROWS_NOTHING(to_string(tile));
    }
}

}

