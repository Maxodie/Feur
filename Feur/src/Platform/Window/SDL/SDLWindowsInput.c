#include "fepch.h"
#include "Platform/Window/SDL/SDLWindowsInput.h"
#include <SDL.h>

Bool FE_API SDLWindowsIsInputPressed_impl(const FE_KeyCode key_code)
{
	return SDL_GetKeyboardState(NULL)[key_code];
}

Bool FE_API SDLWindowsIsInputDown_impl(const FE_KeyCode key_code)
{
	//assert(false,"\n----------\nERROR : Get Key Down for windows not implemented yet.\n----------\n");
	FE_CORE_ASSERT(FALSE, "Get Key Down for windows not implemented yet.");
	return FALSE;
}