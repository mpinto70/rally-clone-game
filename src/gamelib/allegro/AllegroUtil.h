#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/bitmap.h>

#include <cstdio>
#include <memory>
#include <typeinfo>

namespace gamelib {
namespace allegro {
template <typename T>
using destroyFunction = void (*)(T*);

template <typename T>
class Destroyer {
public:
    explicit Destroyer(void (*destroyFunction)(T*))
          : destroyFunction_(destroyFunction) {
        fprintf(stderr, "MHPA %s (%d) - creating deleter for: type = %s\n", __FILE__, __LINE__, typeid(destroyFunction_).name());
    }

    void operator()(T* object) {
        const auto name = typeid(destroyFunction_).name();
        fprintf(stderr, "MHPA %s (%d) - deleting: type = %s / address = %p\n", __FILE__, __LINE__, name, (void*) object);
        destroyFunction_(object);
        fprintf(stderr, "MHPA %s (%d) - deleted: type = %s / address = %p\n", __FILE__, __LINE__, name, (void*) object);
    }

private:
    void (*destroyFunction_)(T*);
};

template <typename T>
Destroyer<T> make_destroyer(void (*destroyFunction)(T* _)) {
    return Destroyer<T>(destroyFunction);
}

template <typename TYPE>
using ALLEGRO_PTR = std::unique_ptr<TYPE, Destroyer<TYPE>>;

using DISPLAY_PTR = ALLEGRO_PTR<ALLEGRO_DISPLAY>;
using BITMAP_PTR = ALLEGRO_PTR<ALLEGRO_BITMAP>;
using FONT_PTR = ALLEGRO_PTR<ALLEGRO_FONT>;
using TIMER_PTR = ALLEGRO_PTR<ALLEGRO_TIMER>;
using EVENT_QUEUE_PTR = ALLEGRO_PTR<ALLEGRO_EVENT_QUEUE>;
}
}
