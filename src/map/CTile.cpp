#include "CTile.h"

#include "util/CException.h"
#include "util/EUtil.h"

namespace map {

CTile::CTile(ETile type,
             EAction action)
    : type_(type),
      action_(action) {
    if (action_ != EAction::NO_ACTION
            && type_ != ETile::ROAD) {
        throw util::CException("CTile - incompatible type "
                               + to_string(type_)
                               + " and action "
                               + to_string(action_)
                               , 1);
    }
}

CTile::~CTile() {
}

}
