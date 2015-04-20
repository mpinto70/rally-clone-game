
#include "game/CController.h"

#include "util/CException.h"
#include "util/CWait.h"

namespace game {

CController::CController(std::unique_ptr<gamelib::IGameLib> & gameLib)
    : gameLib_(std::move(gameLib)) {
    if (gameLib_.get() == nullptr)
        throw util::CException("CController - game lib was null", 1);
}

CController::~CController() {
}

void CController::run() {
    while (not gameLib_->keyboard().isKeyPressed(gamelib::EKey::ESCAPE)) {
        util::CWait wait(10);

        wait.wait();
    }
}

}
