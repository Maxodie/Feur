#include "fepch.h"
#include "Platform/Windows/SDL/SDLWindowsInput.h"
#include <SDL.h>

BOOL SDLWindowsIsInputPressed_impl(Uint8 key_code)
{
	return SDL_GetKeyboardState(NULL)[key_code];
}

BOOL SDLWindowsIsInputDown_impl(Uint8 key_code)
{
	//assert(false,"\n----------\nERROR : Get Key Down for windows not implemented yet.\n----------\n");
	assert(FALSE);
	return FALSE;
}
