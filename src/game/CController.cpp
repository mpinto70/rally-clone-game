
#include "game/CController.h"

#include "map/CMapIO.h"

#include "util/CException.h"
#include "util/CWait.h"

#include <boost/filesystem.hpp>

namespace game {

CController::CController(std::unique_ptr<gamelib::IGameLib>& gameLib,
                         const std::string& pathToRallyDir,
                         const size_t parts)
    : gameLib_(std::move(gameLib)),
      pathToRoot_(pathToRallyDir),
      map_(nullptr),
      parts_(parts) {
    if (gameLib_.get() == nullptr) {
        throw util::CException("CController - game lib was null", 1);
    }
    if (parts == 0) {
        throw std::invalid_argument("CController - zero parts");
    }
    boost::filesystem::path root(pathToRoot_);
    boost::filesystem::path stage0 = root / "stages" / "stage0.dat";
    if (not boost::filesystem::exists(stage0)) {
        throw util::CException("CController - stage not found " + stage0.string(), 1);
    }

    map_.reset(new map::CMap(map::CMapIO::read(stage0.string())));
}

CController::~CController() {
}

void CController::run() {
    using gamelib::EKey;

    size_t x = 0, y = 0;
    while (not gameLib_->keyboard().isKeyPressed(gamelib::EKey::ESCAPE)) {
        util::CWait wait(10);

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
