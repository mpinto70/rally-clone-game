#pragma once

#include <allegro5/allegro_font.h>
#include <allegro5/bitmap.h>

#include <memory>

namespace gamelib {
namespace allegro {

using BITMAP_PTR = std::unique_ptr<ALLEGRO_BITMAP, void (*)(ALLEGRO_BITMAP*)>;
using FONT_PTR = std::unique_ptr<ALLEGRO_FONT, void (*)(ALLEGRO_FONT*)>;
using DISPLAY_PTR = std::unique_ptr<ALLEGRO_DISPLAY, void (*)(ALLEGRO_DISPLAY*)>;
using TIMER_PTR = std::unique_ptr<ALLEGRO_TIMER, void (*)(ALLEGRO_TIMER*)>;
using EVENT_QUEUE_PTR = std::unique_ptr<ALLEGRO_EVENT_QUEUE, void (*)(ALLEGRO_EVENT_QUEUE*)>;
}
}
