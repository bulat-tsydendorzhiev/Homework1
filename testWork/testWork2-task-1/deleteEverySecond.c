#include <stdlib.h>

#include "list.h"

void deleteEverySecond(List* list)
{
	for (size_t i = 0; i < getLength(list); i++)
	{
		if (i % 2 == 1)
		{
			deleteListElement(list, i);
		}
	}
}