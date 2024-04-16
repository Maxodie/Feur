#pragma once
#include <inttypes.h>

typedef enum keySate keySate;

typedef struct
{
	BOOL (*GetKeyPressed)(uint8_t);
	BOOL (*GetKeyDown)(uint8_t);
} Input_API;

Input_API g_Input_API;


void InitInputAPI();

BOOL IsInputPressed(uint8_t key_code);
