
#include "CGraphicMock.h"

namespace gamelib {
namespace mck {

CGraphicMock::~CGraphicMock() {
}

void CGraphicMock::printText(const std::string & text,
                             const GFONT font,
                             const unsigned x,
                             const unsigned y,
                             const COLOR foreground,
                             const COLOR background) {

}

void CGraphicMock::draw(const map::CMap & map,
                        const size_t x,
                        const size_t y,
                        const size_t parts) {
}

void CGraphicMock::flip() {
}

}
}
