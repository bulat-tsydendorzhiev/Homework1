#include <stdlib.h>
#include <stdbool.h>

#include "IntStack.h"

struct IntStack
{
	int value;
	struct IntStack* previous;
};

bool intStackIsEmpty(IntStack* head)
{
	return head == NULL;
}

IntErrorCode pushInt(IntStack** head, const int value)
{
	IntStack* next = malloc(sizeof(IntStack));
	if (next == NULL)
	{
		return outOfMemoryIntStack;
	}
	next->value = value;
	next->previous = *head;
	*head = next;
	return okIntStack;
}

IntErrorCode popInt(IntStack** head)
{
	if (intStackIsEmpty(*head))
	{
		return IntStackIsEmpty;
	}
	IntStack* trash = *head;
	*head = (*head)->previous;
	free(trash);
	return okIntStack;
}

IntErrorCode clearIntStack(IntStack** head)
{
	if (intStackIsEmpty(*head))
	{
		return IntStackIsEmpty;
	}

	IntStack* next = (*head)->previous;
	while (!intStackIsEmpty(next))
	{
		IntStack* temp = next;
		next = next->previous;
		free(temp);
	}
	*head = NULL;
	return okIntStack;
}

int topInt(IntStack* head, IntErrorCode* errorCode)
{
	if (intStackIsEmpty(head))
	{
		*errorCode = IntStackIsEmpty;
		return 1;
	}
	return head->value;
}