#pragma once

typedef enum keySate keySate;

typedef struct Input_API
{
	Bool (*GetKeyPressed)(FE_KeyCode);
	Bool (*GetKeyDown)(FE_KeyCode);
} Input_API;


void FE_API InitInputAPI();

Bool FE_API IsInputPressed(FE_KeyCode key_code);
