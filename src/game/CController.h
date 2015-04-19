
#pragma once

#include "gamelib/IGameLib.h"
#include <memory>
namespace game {

class CController {
    public:
        CController(std::unique_ptr<gamelib::IGameLib> & gameLib);
        ~CController();
    private:
        std::unique_ptr<gamelib::IGameLib> gameLib_;
};

}
