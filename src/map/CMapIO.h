#pragma once

#include "map/CMap.h"

#include <string>
#include <istream>
#include <ostream>

namespace map {

class CMapIO {
    public:
    static CMap read(const std::string & fileName);
    static void write(const std::string & fileName, const CMap & map);
    static CMap read(std::istream & is);
    static void write(std::ostream & os, const CMap & map);
};

}
