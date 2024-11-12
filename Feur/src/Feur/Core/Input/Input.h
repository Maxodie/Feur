#pragma once

typedef enum keySate keySate;

typedef struct Input_API
{
	Bool (*GetKeyPressed)(FE_KeyCode);
	Bool (*GetKeyDown)(FE_KeyCode);
} Input_API;


void FE_DECL InitInputAPI();

Bool FE_DECL IsInputPressed(FE_KeyCode key_code);
