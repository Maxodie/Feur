#include "fepch.h"
#include "Platform/Windows/SDL/SDLWindowsInput.h"
#include <SDL.h>

BOOL FE_API SDLWindowsIsInputPressed_impl(const FE_KeyCode key_code)
{
	return SDL_GetKeyboardState(NULL)[key_code];
}

BOOL FE_API SDLWindowsIsInputDown_impl(const FE_KeyCode key_code)
{
	//assert(false,"\n----------\nERROR : Get Key Down for windows not implemented yet.\n----------\n");
	FE_CORE_ASSERT(FALSE, "ERROR : Get Key Down for windows not implemented yet.");
	return FALSE;
}