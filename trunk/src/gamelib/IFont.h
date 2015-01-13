
#pragma once

// How to address this?
#include <string>
#include <allegro.h>

namespace gamelib {

enum class GFONT : unsigned char {
    SYSTEM_FONT = 1,
    MENU_FONT,
};

class IFont {
    public:
        virtual ~IFont() = 0;
        virtual void setFont(GFONT font) = 0;
		
		// In order to use struct BITMAP and std::string, I opted for include those header files, how could we manage this?
		// Create another class that represents a "BITMAP" ?
		virtual void printText(std::string text, BITMAP * buffer, unsigned x, unsigned y, int foregroundColor, int backgroundColor) = 0;
};

}
