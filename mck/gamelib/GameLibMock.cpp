#include "GameLibMock.h"

#include "util/Exception.h"

#include <memory>

namespace gamelib {
namespace mck {

GameLibMock::GameLibMock(std::unique_ptr<Graphic> & graphic,
                           std::unique_ptr<Sound> & sound,
                           std::unique_ptr<Timer> & timer,
                           std::unique_ptr<Keyboard> & keyboard)
    : graphic_(std::move(graphic)),
      sound_(std::move(sound)),
      timer_(std::move(timer)),
      keyboard_(std::move(keyboard)) {

    if (graphic_.get() == nullptr)
        throw util::Exception("CGameLibMock - graphic was null", 1);
    if (sound_.get() == nullptr)
        throw util::Exception("CGameLibMock - sound was null", 1);
    if (timer_.get() == nullptr)
        throw util::Exception("CGameLibMock - timer was null", 1);
    if (keyboard_.get() == nullptr)
        throw util::Exception("CGameLibMock - keyboard was null", 1);
}

GameLibMock::~GameLibMock() {
}

}
}
