#pragma once

#include "map/CMap.h"

#include <string>

namespace map {

class CMapIO {
    public:
        static CMap read(const std::string & fileName);
        static void write(const std::string & fileName, const CMap & map);
};

}
