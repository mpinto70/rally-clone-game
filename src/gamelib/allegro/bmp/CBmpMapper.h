#pragma once

#include "gamelib/allegro/bmp/CBitmapReader.h"
#include "util/CException.h"
#include "util/EUtil.h"

#include <allegro.h>
#include <map>
#include <memory>
#include <typeinfo>

namespace gamelib {
namespace allegro {
namespace bmp {

template <typename ENUM>
class CBmpMapper {
public:
    typedef ENUM enum_type;

    CBmpMapper(const std::string& fileName,
          unsigned subBmpWidth,
          unsigned subBmpHeight,
          unsigned gap)
          : fullBitmap_(nullptr, destroy_bitmap) {
        auto bmps = CBitmapReader::readBmps(fileName, subBmpWidth, subBmpHeight, gap);
        fullBitmap_.swap(bmps.first);
        typedef typename std::underlying_type<ENUM>::type enum_t;

        const auto qttyRead = bmps.second.size();
        const auto qttyExpected = static_cast<enum_t>(ENUM::LAST);
        if (qttyRead != qttyExpected) {
            throw util::CException("CBmpMapper - number of bmps read ("
                                         + std::to_string(qttyRead)
                                         + ") differs from the expected ("
                                         + std::to_string(qttyExpected)
                                         + ") in "
                                         + fileName
                                         + " for "
                                         + typeid(ENUM).name(),
                  1);
        }
        for (auto bmpId : util::CEnumIterator<ENUM>()) {
            const auto index = static_cast<enum_t>(bmpId);
            bmpMap_.insert(std::make_pair(bmpId, std::move(bmps.second.at(index))));
        }
    }

    virtual ~CBmpMapper() {
        bmpMap_.clear();
        fullBitmap_.reset();
    }

    CBmpMapper(const CBmpMapper&) = delete;
    CBmpMapper& operator=(const CBmpMapper&) = delete;

    CBmpMapper(CBmpMapper&& rhs)
          : bmpMap_(std::move(rhs.bmpMap_)),
            fullBitmap_(std::move(rhs.fullBitmap_)) {
    }

    CBmpMapper& operator=(CBmpMapper&& rhs) {
        bmpMap_.clear();
        fullBitmap_.reset();
        fullBitmap_ = std::move(rhs.fullBitmap_);
        bmpMap_ = std::move(rhs.bmpMap_);
        return *this;
    }

    BITMAP* fullBmp() const {
        return fullBitmap_.get();
    }

    BITMAP* operator[](ENUM bmpId) const {
        return subBmp(bmpId);
    }

    template <typename T>
    BITMAP* operator[](T t) const {
        return subBmp(t);
    }

    BITMAP* subBmp(ENUM bmpId) const {
        const auto it = bmpMap_.find(bmpId);
        if (it == bmpMap_.end())
            throw util::CException("CBmpMapper - bmp not found ("
                                         + std::to_string(static_cast<int>(bmpId))
                                         + ") for "
                                         + typeid(ENUM).name(),
                  1);
        else {
            return it->second.get();
        }
    }

    template <typename T>
    BITMAP* subBmp(T t) const {
        auto tl = util::to_Enum<ENUM, T>(t);
        return subBmp(tl);
    }

    size_t numBmps() const {
        return bmpMap_.size();
    }

private:
    std::map<ENUM, BITMAP_PTR> bmpMap_;
    BITMAP_PTR fullBitmap_;
};
}
}
}
