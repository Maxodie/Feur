#pragma once

typedef enum keySate keySate;

typedef struct
{
	BOOL (*GetKeyPressed)(FE_KeyCode);
	BOOL (*GetKeyDown)(FE_KeyCode);
} Input_API;

Input_API g_Input_API;


void InitInputAPI();

BOOL IsInputPressed(FE_KeyCode key_code);
