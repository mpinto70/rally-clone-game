#pragma once

#include "../mck/gamelib/GameLibMock.h"

namespace gamelib {
namespace mck {

class GameLibUtils {
public:
    static std::unique_ptr<GameLib> createDefault();
};
}
}
