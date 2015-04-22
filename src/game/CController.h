
#pragma once

#include "gamelib/IGameLib.h"
#include "map/CMap.h"

#include <memory>

namespace game {

class CController {
    public:
        explicit CController(std::unique_ptr<gamelib::IGameLib> & gameLib,
                             const std::string & pathToRallyDir);
        ~CController();
        void run();
    private:
        std::unique_ptr<gamelib::IGameLib> gameLib_;
        std::string pathToRoot_;
        std::unique_ptr<map::CMap> map_;
};

}
