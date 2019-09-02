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

constexpr unsigned SIZE_MULTIPLIER = 3;

template <typename ENUM>
class SpriteMapper {
public:
    using enum_type = ENUM;

    SpriteMapper(const std::string& fileName,
          const unsigned spriteWidth,
          const unsigned spriteHeight,
          const unsigned leftFirst,
          const unsigned topFirst,
          const unsigned numColumns,
          const unsigned numRows)
          : fullImage_(nullptr, al_destroy_bitmap), imageWidth_(spriteWidth), imageHeight_(spriteHeight) {
        auto sprites = SpriteReader::readImages(fileName, spriteWidth, spriteHeight, leftFirst, topFirst, numColumns, numRows);
        fullImage_.swap(sprites.first);
        using enum_t = typename std::underlying_type<ENUM>::type;

        const auto qttyRead = sprites.second.size();
        const auto qttyExpected = static_cast<enum_t>(ENUM::LAST);
        if (qttyRead != qttyExpected) {
            throw util::Exception("SpriteMapper - number of sprites read ("
                                        + std::to_string(qttyRead)
                                        + ") differs from the expected ("
                                        + std::to_string(qttyExpected)
                                        + ") in "
                                        + fileName
                                        + " for "
                                        + typeid(ENUM).name(),
                  1);
        }
        for (auto spriteId : util::EnumIterator<ENUM>()) {
            const auto index = static_cast<enum_t>(spriteId);
            spriteMap_.insert(std::make_pair(spriteId, std::move(sprites.second.at(index))));
        }
    }

    virtual ~SpriteMapper() {
        spriteMap_.clear();
        fullImage_.reset();
    }

    SpriteMapper(const SpriteMapper&) = delete;
    SpriteMapper& operator=(const SpriteMapper&) = delete;

    SpriteMapper(SpriteMapper&& rhs) noexcept = default;
    SpriteMapper& operator=(SpriteMapper&& rhs) noexcept = default;

    [[nodiscard]] ALLEGRO_BITMAP* fullImage() const {
        return fullImage_.get();
    }

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
    ALLEGRO_BITMAP* image(T bmpId) const {
        auto tl = util::to_Enum<ENUM, T>(bmpId);
        return image(tl);
    }

    [[nodiscard]] size_t numImages() const {
        return spriteMap_.size();
    }

    [[nodiscard]] unsigned imageWidth() const {
        return imageHeight_;
    }

    [[nodiscard]] unsigned imageHeight() const {
        return imageWidth_;
    }

private:
    std::map<ENUM, BITMAP_PTR> spriteMap_;
    BITMAP_PTR fullImage_;
    unsigned imageWidth_;
    unsigned imageHeight_;
};
}
}
}
