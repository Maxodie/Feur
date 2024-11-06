#pragma once
#include "Feur/Core/Application.h"
extern void FE_API StartSandbox();

int FE_API main(void)
{
	StartApp_impl();

	StartSandbox(); // TODO : setup default layer

	RunApp_impl();

	return 0;
}