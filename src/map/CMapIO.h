#pragma once

#include "map/CMap.h"

#include <string>
#include <istream>
#include <ostream>

namespace map {

class CMapIO {
    public:
        /** reads a map from file named \b fileName
         * @param fileName the name of the map file
         */
        static CMap read(const std::string & fileName);
        /** writes the map \b CMap to file \b fileName
         * @param fileName the name of the map file to be created
         * @param map the map to be written
         */
        static void write(const std::string & fileName, const CMap & map);
        /** reads a map from file the stream \b is
         * @param is the map input stream
         */
        static CMap read(std::istream & is);
        /** writes the map \b CMap to stream \b os
         * @param os the map output stream
         * @param map the map to be written
         */
        static void write(std::ostream & os, const CMap & map);
};

}
