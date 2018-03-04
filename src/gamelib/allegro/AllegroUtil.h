#pragma once

#include <allegro.h>
#include <memory>

namespace gamelib {
namespace allegro {

typedef std::unique_ptr<BITMAP, void (*)(BITMAP*)> BITMAP_PTR;
typedef std::unique_ptr<FONT, void (*)(FONT*)> FONT_PTR;
}
}
