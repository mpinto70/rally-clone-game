#pragma once

#include "gamelib/allegro/bmp/SpriteMapper.h"
#include "map/TileType.h"

#include "util/Exception.h"
#include "util/Util.h"

#include <allegro5/bitmap.h>

#include <map>
#include <memory>
#include <typeinfo>

namespace gamelib {
namespace allegro {
namespace bmp {

class TileMapper {
public:
    using enum_type = map::TileType;

    TileMapper(const std::string& fileName,
          const unsigned leftFirst,
          const unsigned topFirst);

    virtual ~TileMapper() {
        spriteMap_.clear();
        fullImage_.reset();
    }

    TileMapper(const TileMapper&) = delete;
    TileMapper& operator=(const TileMapper&) = delete;

    TileMapper(TileMapper&& rhs) noexcept = default;
    TileMapper& operator=(TileMapper&& rhs) noexcept = default;

    ALLEGRO_BITMAP* operator[](enum_type spriteId) const {
        return image(spriteId);
    }

    template <typename T>
    ALLEGRO_BITMAP* operator[](T t) const {
        return image(t);
    }

    ALLEGRO_BITMAP* image(enum_type spriteId) const {
        const auto it = spriteMap_.find(spriteId);
        if (it == spriteMap_.end())
            throw util::Exception("TileMapper - sprite not found ("
                                        + std::to_string(static_cast<int>(spriteId))
                                        + ") for "
                                        + typeid(enum_type).name(),
                  1);
        else {
            return it->second.get();
        }
    }

    template <typename T>
    ALLEGRO_BITMAP* image(T imgId) const {
        auto tl = util::to_Enum<enum_type, T>(imgId);
        return image(tl);
    }

    [[nodiscard]] size_t numImages() const {
        return spriteMap_.size();
    }

    [[nodiscard]] unsigned imageWidth(enum_type) const {
        return BASE_TILE_SIZE;
    }

    [[nodiscard]] unsigned imageHeight(enum_type) const {
        return BASE_TILE_SIZE;
    }

    [[nodiscard]] unsigned imageWidth(size_t) const {
        return BASE_TILE_SIZE;
    }

    [[nodiscard]] unsigned imageHeight(size_t) const {
        return BASE_TILE_SIZE;
    }

private:
    static constexpr unsigned BASE_TILE_SIZE = 72;

    std::map<enum_type, BITMAP_PTR> spriteMap_;
    BITMAP_PTR fullImage_;
};

enum class TileSource {
    GREEN,
    PINK,
    BROWN,
    BLUE,
    GRAY,
    ORANGE,
    LIGHT_GRAY,
    LIGHT_GREEN,
    LAST,
    FIRST = GREEN
};

std::string to_string(TileSource);

TileMapper createTileMapper(const std::string& file_name, TileSource);
}
}
}
