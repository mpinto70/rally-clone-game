#pragma once

#include "map/Map.h"

#include <istream>
#include <ostream>
#include <string>

namespace map {

class CMapIO {
public:
    /** reads a map from file named \b fileName
     * @param fileName the name of the map file
     */
    static Map read(const std::string& fileName);
    /** writes the map \b CMap to file \b fileName
     * @param fileName the name of the map file to be created
     * @param map the map to be written
     */
    static void write(const std::string& fileName, const Map& map);
    /** reads a map from file the stream \b is
     * @param is the map input stream
     */
    static Map read(std::istream& is);
    /** writes the map \b CMap to stream \b os
     * @param os the map output stream
     * @param map the map to be written
     */
    static void write(std::ostream& os, const Map& map);
};
}
