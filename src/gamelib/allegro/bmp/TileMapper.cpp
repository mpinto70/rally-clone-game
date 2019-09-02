#include "TileMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {

TileMapper createTileMapper(const std::string& file_name, TileSource type) {
    const auto idx = util::from_Enum<unsigned>(type);
    const auto x0 = (idx % 2) * 48 * 7;
    const auto y0 = (idx / 2) * 48 * 4 + 224;
    return TileMapper(file_name, 48, 48, x0, y0, 7, 4);
}

std::string to_string(TileSource enum_value) {
    switch (enum_value) {
        CASE_ENUM_TO_STRING(TileSource::GREEN);
        CASE_ENUM_TO_STRING(TileSource::PINK);
        CASE_ENUM_TO_STRING(TileSource::BROWN);
        CASE_ENUM_TO_STRING(TileSource::BLUE);
        CASE_ENUM_TO_STRING(TileSource::GRAY);
        CASE_ENUM_TO_STRING(TileSource::ORANGE);
        CASE_ENUM_TO_STRING(TileSource::LIGHT_GRAY);
        CASE_ENUM_TO_STRING(TileSource::LIGHT_GREEN);
        case TileSource::LAST:
            break;
    }
    throw util::Exception("to_string(TileSource) - invalid argument", util::from_Enum<int>(enum_value));
}

}
}
}
