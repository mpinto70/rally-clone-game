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
class Destroyer {
public:
    explicit Destroyer(void (*destroyFunction)(T*))
          : destroyFunction_(destroyFunction) {
    }

    void operator()(T* object) {
        destroyFunction_(object);
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
using TIMER_PTR = ALLEGRO_PTR<ALLEGRO_TIMER>;
using EVENT_QUEUE_PTR = ALLEGRO_PTR<ALLEGRO_EVENT_QUEUE>;

#define createBitmap(W, H) ::gamelib::allegro::createElement(al_create_bitmap, al_destroy_bitmap, W, H)
//#define createElement(...) ::gamelib::allegro::createElementFunc(__FILE__, __LINE__, __VA_ARGS__)
template <typename T, typename F, typename... Args>
ALLEGRO_PTR<T> createElement(F createFunction,
      void (*destroyFunction)(T* _),
      Args&&... createArgs) {
    T* object = createFunction(std::forward<Args>(createArgs)...);
    return ALLEGRO_PTR<T>(object, make_destroyer(destroyFunction));
}
}
}
