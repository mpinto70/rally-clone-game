
#pragma once

namespace gamelib {

class IKeyboard {
    public:
		enum KEYS {GLIB_KEY_ENTER, GLIB_KEY_LEFT, GLIB_KEY_RIGHT, GLIB_KEY_UP, GLIB_KEY_DOWN, GLIB_KEY_SPACE};

        virtual ~IKeyboard() = 0;
		virtual bool isKeyPressed(KEYS keyCode) = 0;	
};

}

