#include "Controller.h"

#include "map/MapIO.h"
#include "util/Exception.h"
#include "util/Wait.h"

#include <boost/filesystem.hpp>

namespace game {

Controller::Controller(std::unique_ptr<GameLib>& gameLib,
      const std::string& pathToRallyDir,
      const size_t parts)
      : gameLib_(std::move(gameLib)),
        pathToRoot_(pathToRallyDir),
        map_(nullptr),
        parts_(parts) {
    if (gameLib_.get() == nullptr) {
        throw util::Exception("Controller - game lib was null", 1);
    }
    if (parts == 0) {
        throw std::invalid_argument("Controller - zero parts");
    }
    boost::filesystem::path root(pathToRoot_);
    boost::filesystem::path stage0 = root / "stages" / "stage0.dat";
    if (not boost::filesystem::exists(stage0)) {
        throw util::Exception("Controller - stage not found " + stage0.string(), 1);
    }

    map_.reset(new map::Map(map::MapIO::read(stage0.string())));
}

Controller::~Controller() {
}

void Controller::run() {
    size_t x = 0, y = 0;
    while (not gameLib_->keyboard().isKeyPressed(Key::ESCAPE)) {
        util::Wait wait(10);

        if (gameLib_->keyboard().isKeyPressed(Key::DOWN)) {
            ++y;
            if (y >= map_->height() * parts_) {
                y = 0;
            }
        }
        if (gameLib_->keyboard().isKeyPressed(Key::UP)) {
            if (y == 0) {
                y = map_->height() * parts_;
            }
            --y;
        }
        if (gameLib_->keyboard().isKeyPressed(Key::RIGHT)) {
            ++x;
            if (x >= map_->width() * parts_) {
                x = 0;
            }
        }
        if (gameLib_->keyboard().isKeyPressed(Key::LEFT)) {
            if (x == 0) {
                x = map_->width() * parts_;
            }
            --x;
        }

        gameLib_->graphic().draw(*map_, x, y, parts_);

        wait.wait();
        gameLib_->graphic().flip();
    }
}
}
