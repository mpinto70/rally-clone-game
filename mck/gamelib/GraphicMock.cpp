#include "GraphicMock.h"

namespace gamelib {
namespace mck {

GraphicMock::~GraphicMock() {
}

void GraphicMock::printText(const std::string& text,
      const GFONT font,
      const unsigned x,
      const unsigned y,
      const COLOR foreground,
      const COLOR background) {
}

void GraphicMock::draw(const map::Map& map,
      const size_t x,
      const size_t y,
      const size_t parts) {
}

void GraphicMock::flip() {
}
}
}
