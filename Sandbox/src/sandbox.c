#include "Feur.h"

void Update()
{
	if (IsInputPressed(FE_KEYCODE_H))
	{
		FE_LOG_WARNING("test : {0} %d", 5, 10);
		FE_ASSERT(FALSE, "test");
	}
}