
#pragma once

#include "gamelib/IGameLib.h"

#include <memory>

namespace gamelib {
namespace mck {

class CGameLibMock : public IGameLib {
    public:
        CGameLibMock(std::unique_ptr<IGraphic> & graphic,
                     std::unique_ptr<ISound> & sound,
                     std::unique_ptr<ITimer> & timer,
                     std::unique_ptr<IKeyboard> & keyboard);
        ~CGameLibMock() override;
        IGraphic & graphic() override { return *graphic_; }
        ISound & sound() override { return *sound_; }
        ITimer & timer() override { return *timer_; }
        IKeyboard & keyboard() override { return *keyboard_; }
    private:
        std::unique_ptr<IGraphic> graphic_;
        std::unique_ptr<ISound> sound_;
        std::unique_ptr<ITimer> timer_;
        std::unique_ptr<IKeyboard> keyboard_;
};

}
}
