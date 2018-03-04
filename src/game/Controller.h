#pragma once

#include "gamelib/GameLib.h"
#include "map/Map.h"

#include <memory>

namespace game {

class Controller {
public:
    explicit Controller(std::unique_ptr<gamelib::GameLib>& gameLib,
          const std::string& pathToRallyDir,
          size_t parts);
    ~Controller();
    void run();

private:
    std::unique_ptr<gamelib::GameLib> gameLib_;
    std::string pathToRoot_;
    std::unique_ptr<map::Map> map_;
    size_t parts_;
};
}
