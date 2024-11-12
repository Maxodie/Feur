#pragma once
#include "Feur/Core/Application.h"
extern void FE_DECL StartSandbox();

int FE_DECL main(void)
{
	StartApp_impl();

	StartSandbox(); // TODO : setup default layer

	RunApp_impl();

	return 0;
}