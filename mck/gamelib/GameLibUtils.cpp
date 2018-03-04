#include "GameLibUtils.h"

#include "../mck/gamelib/GameLibMock.h"
#include "../mck/gamelib/GraphicMock.h"
#include "../mck/gamelib/KeyboardMock.h"
#include "../mck/gamelib/SoundMock.h"
#include "../mck/gamelib/TimerMock.h"

namespace gamelib {
namespace mck {

std::unique_ptr<GameLib> GameLibUtils::createDefault() {
    std::unique_ptr<Graphic> graphic(new GraphicMock());
    std::unique_ptr<Sound> sound(new SoundMock());
    std::unique_ptr<Timer> timer(new TimerMock());
    std::unique_ptr<Keyboard> keyboard(new KeyboardMock());

    std::unique_ptr<GameLib> gameLib(new GameLibMock(graphic, sound, timer, keyboard));
    return gameLib;
}
}
}
