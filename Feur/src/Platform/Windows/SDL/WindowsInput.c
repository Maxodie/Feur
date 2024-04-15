#include "fepch.h"
#include "WindowsInput.h"
#include <SDL.h>

bool windowsIsInputPressed_impl(uint8_t key_code)
{
	return SDL_GetKeyboardState(NULL)[key_code];
}

bool windowsIsInputDown_impl(uint8_t key_code)
{
	//assert(false,"\n----------\nERROR : Get Key Down for windows not implemented yet.\n----------\n");
	assert(false);
	return false;
}
