
#pragma once

#include "gamelib/IGameLib.h"
#include <memory>
namespace game {

class CController {
    public:
        explicit CController(std::unique_ptr<gamelib::IGameLib> & gameLib);
        ~CController();
        void run();
    private:
        std::unique_ptr<gamelib::IGameLib> gameLib_;
};

}
