#pragma once

typedef enum keySate keySate;

typedef struct Input_API
{
	BOOL (*GetKeyPressed)(FE_KeyCode);
	BOOL (*GetKeyDown)(FE_KeyCode);
} Input_API;


void FE_API InitInputAPI();

BOOL FE_API IsInputPressed(FE_KeyCode key_code);
