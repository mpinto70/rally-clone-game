#include "GameLibUtils.h"

#include "../mck/game/GameLibMock.h"
#include "../mck/game/GraphicMock.h"
#include "../mck/game/KeyboardMock.h"
#include "../mck/game/SoundMock.h"
#include "../mck/game/TimerMock.h"

namespace game {
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
