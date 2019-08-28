#pragma once

#include "gamelib/allegro/bmp/BitmapReader.h"
#include "util/Exception.h"
#include "util/Util.h"

#include <allegro.h>

#include <map>
#include <memory>
#include <typeinfo>

namespace gamelib {
namespace allegro {
namespace bmp {

template <typename ENUM>
class BmpMapper {
public:
    using enum_type = ENUM;

    BmpMapper(const std::string& fileName,
          unsigned subBmpWidth,
          unsigned subBmpHeight,
          unsigned gap)
          : fullBitmap_(nullptr, destroy_bitmap), imageWidth_(subBmpWidth), imageHeight_(subBmpHeight) {
        auto bmps = BitmapReader::readImages(fileName, subBmpWidth, subBmpHeight, gap);
        fullBitmap_.swap(bmps.first);
        using enum_t = typename std::underlying_type<ENUM>::type;

        const auto qttyRead = bmps.second.size();
        const auto qttyExpected = static_cast<enum_t>(ENUM::LAST);
        if (qttyRead != qttyExpected) {
            throw util::Exception("BmpMapper - number of bmps read ("
                                        + std::to_string(qttyRead)
                                        + ") differs from the expected ("
                                        + std::to_string(qttyExpected)
                                        + ") in "
                                        + fileName
                                        + " for "
                                        + typeid(ENUM).name(),
                  1);
        }
        for (auto bmpId : util::EnumIterator<ENUM>()) {
            const auto index = static_cast<enum_t>(bmpId);
            bmpMap_.insert(std::make_pair(bmpId, std::move(bmps.second.at(index))));
        }
    }

    virtual ~BmpMapper() {
        bmpMap_.clear();
        fullBitmap_.reset();
    }

    BmpMapper(const BmpMapper&) = delete;
    BmpMapper& operator=(const BmpMapper&) = delete;

    BmpMapper(BmpMapper&& rhs) noexcept = default;
    BmpMapper& operator=(BmpMapper&& rhs) noexcept = default;

    [[nodiscard]] BITMAP* fullImage() const {
        return fullBitmap_.get();
    }

    BITMAP* operator[](ENUM bmpId) const {
        return image(bmpId);
    }

    template <typename T>
    BITMAP* operator[](T t) const {
        return image(t);
    }

    BITMAP* image(ENUM bmpId) const {
        const auto it = bmpMap_.find(bmpId);
        if (it == bmpMap_.end())
            throw util::Exception("BmpMapper - bmp not found ("
                                        + std::to_string(static_cast<int>(bmpId))
                                        + ") for "
                                        + typeid(ENUM).name(),
                  1);
        else {
            return it->second.get();
        }
    }

    template <typename T>
    BITMAP* image(T bmpId) const {
        auto tl = util::to_Enum<ENUM, T>(bmpId);
        return image(tl);
    }

    [[nodiscard]] size_t numImages() const {
        return bmpMap_.size();
    }

    [[nodiscard]] unsigned imageWidth() const {
        return imageHeight_;
    }

    [[nodiscard]] unsigned imageHeight() const {
        return imageWidth_;
    }

private:
    std::map<ENUM, BITMAP_PTR> bmpMap_;
    BITMAP_PTR fullBitmap_;
    unsigned imageWidth_;
    unsigned imageHeight_;
};
}
}
}
