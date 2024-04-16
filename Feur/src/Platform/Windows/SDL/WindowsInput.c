#include "fepch.h"
#include "WindowsInput.h"
#include <SDL.h>

BOOL windowsIsInputPressed_impl(uint8_t key_code)
{
	return SDL_GetKeyboardState(NULL)[key_code];
}

BOOL windowsIsInputDown_impl(uint8_t key_code)
{
	//assert(false,"\n----------\nERROR : Get Key Down for windows not implemented yet.\n----------\n");
	assert(FALSE);
	return FALSE;
}
