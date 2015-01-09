/**
 Rally-X Clone - 2015
 main code.
 */

#include "CGameLib.h"
 
// Essas duas constantes ficam por aqui mesmo?
static const unsigned int UTIL_W = 480, UTIL_H = 240;

int main()
{
  int iGameLibResult = GameLib::Init(UTIL_W, UTIL_H);
  iGameLibResult = 0;

  GameLib::End();
  
  return 0;
}
END_OF_MAIN()
