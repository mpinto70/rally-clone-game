/**
 Rally-X Clone 2015
 Wrapper para lib(s) de controle de input/gfx/sfx/misc.
 */

#include "CGameLib.h"

namespace graphic {
// Este cara tem que ser visto por todo mundo que deseja desenhar
// na tela, como pretende fazer isso? No megaman fica numa global :D
// Fica nessa class? Criar uma outra classe pra isso e passar a referencia
// pro init?
BITMAP * GameLib::buffer = NULL;

int GameLib::Init(unsigned int uiWidth, unsigned int uiHeight) {
    int iAllegResult = allegro_init();

    if (iAllegInitResult != 0)
        ;// exception? retorna valor? ignora?

    iAllegResult += install_keyboard();
    iAllegResult += install_timer();

    if (iAllegInitResult != 0)
        ;// exception? retorna valor? ignora?

    iAllegInitResult = install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);

    if (iAllegInitResult != 0)
        ;//Desliga o som ou trata como erro?

    set_color_depth(32);
    iAllegInitResult = set_gfx_mode(GFX_AUTODETECT_WINDOWED, uiWidth, uiHeight, 0, 0);
    if (iAllegInitResult != 0)
        ;//Tenta mudar para outro color depht ou aborta?

    // Cria buffer com a mesma resolução WxH da tela.
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    if (buffer == NULL)
        ;// E ai??

    return 0;
}

void GameLib::End() {
    destroy_bitmap(buffer);
    buffer = NULL;

    // Vale a pena? o processo tá morrendo... Do manual:
    // Note that after you call this function, other functions like destroy_bitmap() will most likely crash.
    // This is a problem for C++ global destructors, which usually get called after atexit(), so don't put
    // Allegro calls in them. You can write the destructor code in another method which you can manually call
    // before your program exits, avoiding this problem.
    allegro_exit();
}

}

