#pragma once

#include "../mck/gamelib/GameLibMock.h"

namespace game {
namespace mck {

class GameLibUtils {
public:
    static std::unique_ptr<GameLib> createDefault();
};
}
}
