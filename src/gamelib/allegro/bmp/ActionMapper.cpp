#include "ActionMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {

ActionMapper::ActionMapper(BITMAP_PTR& fullImage) {
    constexpr unsigned ROAD_X = 0;
    constexpr unsigned ROAD_Y = 336; // height of first road
    constexpr unsigned ROAD_SIZE = 72;
    auto road = SpriteReader::readImages(fullImage, ROAD_SIZE, ROAD_SIZE, ROAD_X, ROAD_Y, 1, 1);

    constexpr unsigned PLAYER_X = 0;
    constexpr unsigned PLAYER_Y = 0;
    constexpr unsigned PLAYER_SIZE = 48;
    auto player = SpriteReader::readImages(fullImage, PLAYER_SIZE, PLAYER_SIZE, PLAYER_X, PLAYER_Y, 1, 1);

    constexpr unsigned BANG_X = 0;
    constexpr unsigned BANG_Y = 48 * 5; // 5 = 4 cars + 1 fuel
    constexpr unsigned BANG_SIZE = 72;
    auto bang_rocks_smoke = SpriteReader::readImages(fullImage, BANG_SIZE, BANG_SIZE, BANG_X, BANG_Y, 4, 1);

    constexpr unsigned CAR_X = 0;
    constexpr unsigned CAR_Y = 48 * 1; // 1 = second row of cars
    constexpr unsigned CAR_SIZE = 48;
    constexpr unsigned CAR_GAP = 48 * 2; // 2 cars in each gap
    auto cars = SpriteReader::readImages(fullImage, CAR_SIZE, CAR_SIZE, CAR_X, CAR_Y, 4, 1, CAR_GAP);

    constexpr unsigned FUEL_X = 0;
    constexpr unsigned FUEL_Y = 48 * 4; // 4 = cars
    constexpr unsigned FUEL_SIZE = 48;
    auto fuels = SpriteReader::readImages(fullImage, FUEL_SIZE, FUEL_SIZE, FUEL_X, FUEL_Y, 3, 1);

    using enum_t = typename std::underlying_type<enum_type>::type;

    const auto qttyRead = road.size() + player.size() + bang_rocks_smoke.size() + cars.size() + fuels.size();
    const auto qttyExpected = static_cast<enum_t>(enum_type::LAST);
    if (qttyRead != qttyExpected) {
        throw util::Exception("ActionMapper - number of sprites read ("
                                    + std::to_string(qttyRead)
                                    + ") differs from the expected ("
                                    + std::to_string(qttyExpected)
                                    + ") for "
                                    + typeid(enum_type).name(),
              1);
    }

    using map::from_EAction;

    spriteMap_.insert(std::make_pair(enum_type::NONE, std::move(road[0])));

    spriteMap_.insert(std::make_pair(enum_type::PLAYER, std::move(player[0])));

    spriteMap_.insert(std::make_pair(enum_type::BANG, std::move(bang_rocks_smoke[0])));
    spriteMap_.insert(std::make_pair(enum_type::STONE_1, std::move(bang_rocks_smoke[1])));
    spriteMap_.insert(std::make_pair(enum_type::STONE_2, std::move(bang_rocks_smoke[2])));
    spriteMap_.insert(std::make_pair(enum_type::SMOKE, std::move(bang_rocks_smoke[3])));

    spriteMap_.insert(std::make_pair(enum_type::ENEMY_NORTH, std::move(cars[0])));
    spriteMap_.insert(std::make_pair(enum_type::ENEMY_EAST, std::move(cars[1])));
    spriteMap_.insert(std::make_pair(enum_type::ENEMY_SOUTH, std::move(cars[2])));
    spriteMap_.insert(std::make_pair(enum_type::ENEMY_WEST, std::move(cars[3])));

    spriteMap_.insert(std::make_pair(enum_type::FUEL, std::move(fuels[0])));
    spriteMap_.insert(std::make_pair(enum_type::FUEL_S, std::move(fuels[1])));
    spriteMap_.insert(std::make_pair(enum_type::FUEL_L, std::move(fuels[2])));

    sizes_[enum_type::NONE] = ROAD_SIZE;

    sizes_[enum_type::PLAYER] = PLAYER_SIZE;

    sizes_[enum_type::BANG] = BANG_SIZE;
    sizes_[enum_type::STONE_1] = BANG_SIZE;
    sizes_[enum_type::STONE_2] = BANG_SIZE;
    sizes_[enum_type::SMOKE] = BANG_SIZE;

    sizes_[enum_type::ENEMY_NORTH] = CAR_SIZE;
    sizes_[enum_type::ENEMY_EAST] = CAR_SIZE;
    sizes_[enum_type::ENEMY_SOUTH] = CAR_SIZE;
    sizes_[enum_type::ENEMY_WEST] = CAR_SIZE;

    sizes_[enum_type::FUEL] = FUEL_SIZE;
    sizes_[enum_type::FUEL_S] = FUEL_SIZE;
    sizes_[enum_type::FUEL_L] = FUEL_SIZE;
}

ActionMapper createActionMapper(BITMAP_PTR& fullImage) {
    return ActionMapper(fullImage);
}
}
}
}
