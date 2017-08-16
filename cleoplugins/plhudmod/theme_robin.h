
#include "opcodes.h"

#define ISTHEMEROBIN THEME == THEME_ROBIN

#if ISTHEMEROBIN
void robindrawhookstuff();
#define ROBINHOOKADDR (((DWORD) &robindrawhookstuff) - 0x58EE9F + 1 - 4 - 2)
#else
#define ROBINHOOKADDR (0)
#endif