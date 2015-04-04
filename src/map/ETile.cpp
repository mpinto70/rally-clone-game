
#include "ETile.h"

namespace map {

bool operator < (ETile lhs, ETile rhs) {
    return static_cast<tile_t>(lhs) < static_cast<tile_t>(rhs);
}

}
