#pragma once
#include <stdbool.h>
#include <inttypes.h>

typedef enum keySate keySate;
typedef enum Input_API_Type Input_API_Type;//TODO : put this as window api and put it in window

typedef struct
{
	bool (*GetKeyPressed)(uint8_t);
	bool (*GetKeyDown)(uint8_t);
} Input_API;

Input_API_Type g_Input_API_Type;
Input_API g_Input_API;


void InitInputAPI();

bool IsInputPressed(uint8_t key_code);
