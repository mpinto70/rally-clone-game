#pragma once

#include "GameLibMock.h"

namespace gamelib {
namespace mck {

class GameLibUtils {
public:
    static std::unique_ptr<GameLib> createDefault();
};
}
}
