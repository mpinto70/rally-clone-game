/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de texto.
 */

#include "CFont.h"
#include "util/CException.h"
#include <allegro.h>

namespace gamelib {
namespace allegro {

CFont::CFont() {
    menuFont_ = load_font("resource_dir_address", NULL, NULL);
	
	if (menuFont_ == NULL)
	{
	  throw util::CException("CFont::CFont - Error initializing font subsystem", 0);
	}
}

CFont::~CFont() {
}

void setFont(GFONT font) {
  switch(font) {
    case SYSTEM_FONT:
	  font_ = font;
	break;
	case MENU_FONT:
	  font_ = menuFont_;
	break;
  }
}

void printText(std::string text, BITMAP * buffer, unsigned x, unsigned y, int foregroundColor, int backgroundColor) {
  if (buffer == NULL); // this have zero reason to occur...

  // Just return, don't see any reason to treat it like an error.
  if (text.empty() == true) return;
  
  // Outside bitmap boundaries.
  if ((x > buffer->w) || (y > buffer->h)) return;
  
  textout_ex(buffer, font_, text.c_str(), x, y, foregroundColor, backgroundColor);
}

}
}

