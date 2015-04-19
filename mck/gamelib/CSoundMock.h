
#pragma once

#include "gamelib/ISound.h"

namespace gamelib {
namespace mck {

class CSoundMock : public ISound {
    public:
        ~CSoundMock() override;
};

}
}
