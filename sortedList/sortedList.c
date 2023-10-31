#include <stdlib.h>
#include <stdio.h>

#include "sortedList.h"

typedef struct Node
{
	int value;
	struct Node* next;
} Node;

ErrorCode pushValue(Node** list, const int value)
{
	Node* temp = malloc(sizeof(Node));
	if (temp == NULL)
	{
		return outOfMemory;
	}

	temp->value = value;

	if (*list == NULL || value < (*list)->value)
	{
		temp->next = *list;
		*list = temp;
	}
	else
	{
		Node* head = *list;
		while (head->next != NULL && head->next->value < value)
		{
			head = head->next;
		}
		temp->next = head->next;
		head->next = temp;
	}
	return ok;
}

ErrorCode deleteValue(Node** list, const int value)
{
	if (*list == NULL)
	{
		return listIsEmpty;
	}

	Node* deletingNode = (*list);
	Node* previousNode = NULL;

	if (deletingNode != NULL && deletingNode->value == value) {
		*list = deletingNode->next;
		free(deletingNode);
		return ok;
	}

	while (deletingNode != NULL && deletingNode->value != value)
	{
		previousNode = deletingNode;
		deletingNode = deletingNode->next;
	}

	if (deletingNode == NULL)
	{
		return deletingANonExistentElement;
	}
	else
	{
		previousNode->next = deletingNode->next;
		free(deletingNode);
	}
	return ok;
}

void printList(Node* list)
{
	while (list != NULL)
	{
		printf("%d ", list->value);
		list = list->next;
	}
	printf("\n");
}

ErrorCode clearList(Node** list)
{
	if (*list == NULL)
	{
		return listIsEmpty;
	}

	while ((*list) != NULL)
	{
		Node* trash = *list;
		*list = (*list)->next;
		free(trash);
	}
	return ok;
}
