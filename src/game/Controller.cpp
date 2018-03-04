#include "Controller.h"

#include "map/MapIO.h"
#include "util/Exception.h"
#include "util/Wait.h"

#include <boost/filesystem.hpp>

namespace game {

Controller::Controller(std::unique_ptr<gamelib::GameLib>& gameLib,
      const std::string& pathToRallyDir,
      const size_t parts)
      : gameLib_(std::move(gameLib)),
        pathToRoot_(pathToRallyDir),
        map_(nullptr),
        parts_(parts) {
    if (gameLib_.get() == nullptr) {
        throw util::Exception("CController - game lib was null", 1);
    }
    if (parts == 0) {
        throw std::invalid_argument("CController - zero parts");
    }
    boost::filesystem::path root(pathToRoot_);
    boost::filesystem::path stage0 = root / "stages" / "stage0.dat";
    if (not boost::filesystem::exists(stage0)) {
        throw util::Exception("CController - stage not found " + stage0.string(), 1);
    }

    map_.reset(new map::Map(map::CMapIO::read(stage0.string())));
}

Controller::~Controller() {
}

void Controller::run() {
    using gamelib::EKey;

    size_t x = 0, y = 0;
    while (not gameLib_->keyboard().isKeyPressed(gamelib::EKey::ESCAPE)) {
        util::Wait wait(10);

        if (gameLib_->keyboard().isKeyPressed(EKey::DOWN)) {
            ++y;
            if (y >= map_->height() * parts_) {
                y = 0;
            }
        }
        if (gameLib_->keyboard().isKeyPressed(EKey::UP)) {
            if (y == 0) {
                y = map_->height() * parts_;
            }
            --y;
        }
        if (gameLib_->keyboard().isKeyPressed(EKey::RIGHT)) {
            ++x;
            if (x >= map_->width() * parts_) {
                x = 0;
            }
        }
        if (gameLib_->keyboard().isKeyPressed(EKey::LEFT)) {
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
