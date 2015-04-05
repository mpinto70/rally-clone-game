#pragma once

#include "map/EMapUtil.h"
#include "util/EUtil.h"
#include <cstdint>
#include <stdexcept>
#include <string>

/** namespaces of elements related to maps. */
namespace map {

typedef std::uint8_t action_t;
/** Types of tiles. */
enum class EAction : action_t {
    NONE,
    CREATE_ENEMY,
    CREATE_STONE,
    LAST,
    FIRST = NONE
};

template <typename T>
EAction to_EAction(T t) {
    return util::to_Enum<EAction, T>(t);
}

std::string to_string(EAction tile);

}

