#pragma once

typedef struct FE_App
{
	WindowData windowData;
} FE_App;

FE_App g_fe_App;

void RunApp_impl();