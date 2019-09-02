#pragma once

#include <allegro5/allegro_font.h>
#include <allegro5/bitmap.h>

#include <memory>

namespace gamelib {
namespace allegro {

using BITMAP_PTR = std::unique_ptr<ALLEGRO_BITMAP, void (*)(ALLEGRO_BITMAP*)>;
using FONT_PTR = std::unique_ptr<ALLEGRO_FONT, void (*)(ALLEGRO_FONT*)>;
}
}
