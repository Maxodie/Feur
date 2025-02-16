#pragma once

typedef enum keySate keySate;

typedef struct Input_API
{
	Bool (*GetKeyPressed)(FE_KeyCode);
	Bool (*GetKeyDown)(FE_KeyCode);
} Input_API;


void FE_DECL FE_InitInputAPI();

Bool FE_DECL FE_IsInputPressed(FE_KeyCode key_code);
const ILDA_vector2d* GetCursorPosition();