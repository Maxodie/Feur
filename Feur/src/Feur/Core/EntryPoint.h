#pragma once
#include "Feur/Core/Application.h"

extern void StartSandbox();

int main(void)
{
	StartApp_impl();

	StartSandbox(); // TODO : setup default layer

	RunApp_impl();

	return 0;
}