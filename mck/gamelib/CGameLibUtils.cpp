
#include "CGameLibUtils.h"
#include "../mck/gamelib/CGameLibMock.h"
#include "../mck/gamelib/CGraphicMock.h"
#include "../mck/gamelib/CSoundMock.h"
#include "../mck/gamelib/CTimerMock.h"
#include "../mck/gamelib/CKeyboardMock.h"

namespace gamelib {
namespace mck {

std::unique_ptr<IGameLib> CGameLibUtils::createDefault() {
    std::unique_ptr<IGraphic> graphic(new CGraphicMock());
    std::unique_ptr<ISound> sound(new CSoundMock());
    std::unique_ptr<ITimer> timer(new CTimerMock());
    std::unique_ptr<IKeyboard> keyboard(new CKeyboardMock());

    std::unique_ptr<IGameLib> gameLib(new CGameLibMock(graphic, sound, timer, keyboard));
    return gameLib;
}
}

}
