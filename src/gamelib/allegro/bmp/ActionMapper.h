#pragma once

#include "gamelib/allegro/bmp/SpriteReader.h"
#include "map/Action.h"
#include "util/Exception.h"
#include "util/Util.h"

#include <allegro5/bitmap.h>

#include <map>
#include <memory>
#include <typeinfo>

namespace gamelib {
namespace allegro {
namespace bmp {

class ActionMapper {
public:
    using enum_type = map::Action;

    explicit ActionMapper(const std::string& fileName);

    virtual ~ActionMapper() {
        spriteMap_.clear();
        fullImage_.reset();
    }

    ActionMapper(const ActionMapper&) = delete;
    ActionMapper& operator=(const ActionMapper&) = delete;

    ActionMapper(ActionMapper&& rhs) noexcept = default;
    ActionMapper& operator=(ActionMapper&& rhs) noexcept = default;

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
            throw util::Exception("ActionMapper - sprite not found ("
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

    [[nodiscard]] unsigned imageWidth(size_t imgId) const {
        const auto spriteId = map::to_EAction(imgId);
        const auto it = sizes_.find(spriteId);
        if (it == sizes_.end())
            throw util::Exception("ActionMapper - size not found ("
                                        + std::to_string(static_cast<int>(spriteId))
                                        + ") for "
                                        + typeid(enum_type).name(),
                  1);
        else {
            return it->second;
        }
    }

    [[nodiscard]] unsigned imageHeight(size_t imgId) const {
        return imageWidth(imgId);
    }

private:
    std::map<enum_type, BITMAP_PTR> spriteMap_;
    std::map<enum_type, unsigned> sizes_;
    BITMAP_PTR fullImage_;
};

ActionMapper createActionMapper(const std::string& file_name);
}
}
}
