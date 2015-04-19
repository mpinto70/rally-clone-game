#pragma once

#include "../mck/gamelib/CGameLibMock.h"

namespace gamelib {
namespace mck {

class CGameLibUtils {
    public:
        static std::unique_ptr<IGameLib> createDefault();
};

}
}
