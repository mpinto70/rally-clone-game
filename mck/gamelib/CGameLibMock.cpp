
#include "CGameLibMock.h"
#include "util/CException.h"

#include <memory>

namespace gamelib {
namespace mck {

CGameLibMock::CGameLibMock(std::unique_ptr<IGraphic> & graphic,
                           std::unique_ptr<ISound> & sound,
                           std::unique_ptr<ITimer> & timer,
                           std::unique_ptr<IKeyboard> & keyboard)
    : graphic_(std::move(graphic)),
      sound_(std::move(sound)),
      timer_(std::move(timer)),
      keyboard_(std::move(keyboard)) {

    if (graphic_.get() == nullptr)
        throw util::CException("CGameLibMock - graphic was null", 1);
    if (sound_.get() == nullptr)
        throw util::CException("CGameLibMock - sound was null", 1);
    if (timer_.get() == nullptr)
        throw util::CException("CGameLibMock - timer was null", 1);
    if (keyboard_.get() == nullptr)
        throw util::CException("CGameLibMock - keyboard was null", 1);
}

CGameLibMock::~CGameLibMock() {
}

}
}
