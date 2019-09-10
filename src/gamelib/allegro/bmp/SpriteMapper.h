#pragma once

#include "gamelib/allegro/bmp/SpriteReader.h"
#include "util/Exception.h"
#include "util/Util.h"

#include <allegro5/bitmap.h>

#include <map>
#include <memory>
#include <typeinfo>

namespace gamelib {
namespace allegro {
namespace bmp {

template <typename ENUM>
class SpriteMapper final {
public:
    using enum_type = ENUM;

    SpriteMapper(const BITMAP_PTR& fullImage,
          const unsigned spriteWidth,
          const unsigned spriteHeight,
          const unsigned leftFirst,
          const unsigned topFirst,
          const unsigned numColumns,
          const unsigned numRows)
          : imageWidth_(spriteWidth), imageHeight_(spriteHeight) {
        auto sprites = SpriteReader::readImages(fullImage, spriteWidth, spriteHeight, leftFirst, topFirst, numColumns, numRows);
        using enum_t = typename std::underlying_type<ENUM>::type;

        const auto qttyRead = sprites.size();
        const auto qttyExpected = static_cast<enum_t>(ENUM::LAST);
        if (qttyRead != qttyExpected) {
            throw util::Exception("SpriteMapper - number of sprites read ("
                                        + std::to_string(qttyRead)
                                        + ") differs from the expected ("
                                        + std::to_string(qttyExpected)
                                        + ") for "
                                        + typeid(ENUM).name(),
                  1);
        }
        for (auto spriteId : util::EnumIterator<ENUM>()) {
            const auto index = static_cast<enum_t>(spriteId);
            spriteMap_.insert(std::make_pair(spriteId, std::move(sprites.at(index))));
        }
    }

    SpriteMapper(const SpriteMapper&) = delete;
    SpriteMapper& operator=(const SpriteMapper&) = delete;

    SpriteMapper(SpriteMapper&& rhs) noexcept = default;
    SpriteMapper& operator=(SpriteMapper&& rhs) noexcept = default;

    ALLEGRO_BITMAP* operator[](ENUM spriteId) const {
        return image(spriteId);
    }

    template <typename T>
    ALLEGRO_BITMAP* operator[](T t) const {
        return image(t);
    }

    ALLEGRO_BITMAP* image(ENUM spriteId) const {
        const auto it = spriteMap_.find(spriteId);
        if (it == spriteMap_.end())
            throw util::Exception("SpriteMapper - sprite not found ("
                                        + std::to_string(static_cast<int>(spriteId))
                                        + ") for "
                                        + typeid(ENUM).name(),
                  1);
        else {
            return it->second.get();
        }
    }

    template <typename T>
    ALLEGRO_BITMAP* image(T imgId) const {
        auto tl = util::to_Enum<ENUM, T>(imgId);
        return image(tl);
    }

    [[nodiscard]] size_t numImages() const {
        return spriteMap_.size();
    }

    [[nodiscard]] unsigned imageWidth(enum_type /*spriteId*/) const {
        return imageHeight_;
    }

    [[nodiscard]] unsigned imageHeight(enum_type /*spriteId*/) const {
        return imageWidth_;
    }

    [[nodiscard]] unsigned imageWidth(size_t /*imgId*/) const {
        return imageHeight_;
    }

    [[nodiscard]] unsigned imageHeight(size_t /*imgId*/) const {
        return imageWidth_;
    }

private:
    std::map<ENUM, BITMAP_PTR> spriteMap_;
    unsigned imageWidth_;
    unsigned imageHeight_;
};
}
}
}
