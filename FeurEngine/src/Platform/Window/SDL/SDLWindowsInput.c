#include "fepch.h"
#include "Platform/Window/SDL/SDLWindowsInput.h"
//#include <SDL.h>

Bool FE_DECL SDLWindowsIsInputPressed_impl(const FE_KeyCode key_code)
{
	FE_CORE_ASSERT(FALSE, "Get Key Down for windows not implemented yet.");
	return FALSE;
	//return SDL_GetKeyboardState(NULL)[key_code];
}

Bool FE_DECL SDLWindowsIsInputDown_impl(const FE_KeyCode key_code)
{
	FE_CORE_ASSERT(FALSE, "Get Key Down for windows not implemented yet.");
	return FALSE;
}