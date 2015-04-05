
#include "testEAction.h"

#include "map/EAction.h"
#include "util/CException.h"

namespace map {

void testEAction::testToString() {
    TS_ASSERT_EQUALS(to_string(EAction::NO_ACTION),     "EAction::NO_ACTION");
    TS_ASSERT_EQUALS(to_string(EAction::CREATE_ENEMY),  "EAction::CREATE_ENEMY");
    TS_ASSERT_EQUALS(to_string(EAction::CREATE_STONE),  "EAction::CREATE_STONE");

    TS_ASSERT_THROWS_EQUALS(to_string(EAction::LAST),
                            util::CException & e,
                            std::string(e.what()),
                            "to_string(EAction) - invalid argument");

    for (const auto tile : util::CEnumIterator<EAction>()) {
        TS_ASSERT_THROWS_NOTHING(to_string(tile));
    }
}

}

