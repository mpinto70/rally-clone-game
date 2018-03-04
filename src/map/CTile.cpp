#include "CTile.h"

#include "util/CException.h"
#include "util/EUtil.h"

namespace map {

CTile::CTile(ETileType type,
      EAction action)
      : type_(type),
        action_(action) {
    if (action_ != EAction::NONE
          && type_ != ETileType::ROAD) {
        throw util::CException("CTile - incompatible type "
                                     + to_string(type_)
                                     + " and action "
                                     + to_string(action_),
              1);
    }
}

CTile::~CTile() {
}

bool operator==(const CTile& lhs, const CTile& rhs) {
    return lhs.type() == rhs.type()
           && lhs.action() == rhs.action();
}

void CTile::type(ETileType type) {
    type_ = type;
    if (type_ != ETileType::ROAD) {
        action_ = EAction::NONE;
    }
}

void CTile::action(EAction action) {
    if (action != EAction::NONE
          && type_ != ETileType::ROAD)
        throw util::CException("CTile::action(action) - incompatible type "
                                     + to_string(type_)
                                     + " and new action "
                                     + to_string(action),
              1);
    action_ = action;
}
}
