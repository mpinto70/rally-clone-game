
#include "IGameLib.h"
#include "util/CSingleton.h"

namespace gamelib {

IGameLib & IGameLib::instance() {
    return util::CSingleton<IGameLib>::instance();
}

IGameLib::~IGameLib() {
}

}

