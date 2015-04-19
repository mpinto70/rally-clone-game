
#include "testCController.h"

#include "game/CController.h"
#include "util/CException.h"

namespace game {

void testCController::testCreation() {
}

void testCController::testInvalidCreation() {
    std::unique_ptr<gamelib::IGameLib> empty;
    TS_ASSERT_THROWS_EQUALS(CController c(empty),
                            util::CException & e,
                            std::string(e.what()),
                            "CController - game lib was null");
}

}

