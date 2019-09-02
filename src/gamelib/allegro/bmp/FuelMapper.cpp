#include "FuelMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {

FuelMapper createFuelMapper(const std::string& file_name) {
    const auto number_of_fuels = util::from_Enum<unsigned>(fuel::Type::LAST);
    return FuelMapper(file_name, 32, 32, 0, 128, number_of_fuels, 1);
}

}
}
}
