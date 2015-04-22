
#include "game/CController.h"

#include "map/CMapIO.h"

#include "util/CException.h"
#include "util/CWait.h"

#include <boost/filesystem.hpp>

namespace game {

CController::CController(std::unique_ptr<gamelib::IGameLib> & gameLib,
                         const std::string & pathToRallyDir)
    : gameLib_(std::move(gameLib)),
      pathToRoot_(pathToRallyDir),
      map_(nullptr) {
    if (gameLib_.get() == nullptr)
        throw util::CException("CController - game lib was null", 1);
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

    while (not gameLib_->keyboard().isKeyPressed(gamelib::EKey::ESCAPE)) {
        util::CWait wait(10);

        gameLib_->graphic().draw(*map_, 0, 0);

        wait.wait();
        gameLib_->graphic().flip();
    }
}

}
