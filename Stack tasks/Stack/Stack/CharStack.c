#include <stdlib.h>

#include "CharStack.h"

struct CharStack
{
	char value;
	struct CharStack* previous;
};

bool charStackIsEmpty(CharStack* head)
{
	return head == NULL;
}

CharErrorCode pushChar(CharStack** head, const char value)
{
	CharStack* next = malloc(sizeof(CharStack));
	if (next == NULL)
	{
		return CharStackIsEmpty;
	}
	next->value = value;
	next->previous = *head;
	*head = next;
	return okCharStack;
}

CharErrorCode popChar(CharStack** head)
{
	if (*head == NULL)
	{
		return CharStackIsEmpty;
	}
	CharStack* trash = *head;
	*head = (*head)->previous;
	free(trash);
	return okCharStack;
}

CharErrorCode clearCharStack(CharStack** head)
{
	if (head == NULL || *head == NULL)
	{
		return CharStackIsEmpty;
	}

	CharStack* next = (*head)->previous;
	while (next != NULL)
	{
		CharStack* temp = next;
		next = next->previous;
		free(temp);
	}
	*head = NULL;
	return okCharStack;
}

char topChar(CharStack* head, CharErrorCode* errorCode)
{
	if (head == NULL)
	{
		*errorCode = CharStackIsEmpty;
		return 1;
	}
	return head->value;
}