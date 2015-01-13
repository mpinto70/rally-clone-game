/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de texto.
*/

#pragma once

#include "gamelib/IFont.h"

namespace gamelib {
namespace allegro {

class CFont : public IFont {
    public:
        CFont();
        ~CFont() override;

		void setFont(GFONT font) override;
		void printText(std::string text, BITMAP * buffer, unsigned x, unsigned y, int foregroundColor, int backgroundColor) override;
	private:
		FONT * font_;
		FONT * menuFont_;
};

}
}

