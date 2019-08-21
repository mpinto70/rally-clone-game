#pragma once

#include <allegro.h>

#include <memory>

namespace gamelib {
namespace allegro {

using BITMAP_PTR = std::unique_ptr<BITMAP, void (*)(BITMAP*)>;
using FONT_PTR = std::unique_ptr<FONT, void (*)(FONT*)>;
}
}
