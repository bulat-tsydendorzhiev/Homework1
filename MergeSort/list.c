#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_NUMBER_LENGTH 20

struct Node
{
	char* name;
	char* phoneNumber;
	struct Node* next;
};

ListErrorCode append(Node** list, const char* name, const char* phoneNumber)
{
	Node* temp = malloc(sizeof(Node));
	if (temp == NULL)
	{
		return listOutOfMemory;
	}
	size_t nameLength = strlen(name) + 1;
	temp->name = malloc(nameLength);
	if (temp->name == NULL)
	{
		return listOutOfMemory;
	}
	strcpy_s(temp->name, nameLength, name);

	size_t phoneNumberLength = strlen(phoneNumber) + 1;
	temp->phoneNumber = malloc(phoneNumberLength);
	if (temp->phoneNumber == NULL)
	{
		return listOutOfMemory;
	}
	strcpy_s(temp->phoneNumber, phoneNumberLength, phoneNumber);
	temp->next = NULL;

	if (*list == NULL)
	{
		*list = temp;
	}
	else
	{
		Node* head = *list;
		while (head->next != NULL)
		{
			head = head->next;
		}
		head->next = temp;
	}
	return okList;
}

ListErrorCode loadData(Node** list, const char* filename)
{
	FILE* file = NULL;
	fopen_s(&file, filename, "r");
	if (file == NULL)
	{
		clearList(*list);
		return listOpenFileError;
	}

	char name[MAX_NAME_LENGTH];
	char phoneNumber[MAX_PHONE_NUMBER_LENGTH];
	while (fscanf_s(file, "%s - %s", name, MAX_NAME_LENGTH, phoneNumber, MAX_PHONE_NUMBER_LENGTH) == 2)
	{
		append(list, name, phoneNumber);
	}

	fclose(file);
	return okList;
}

Node* getNextNode(Node* node, ListErrorCode* errorCode)
{
	if (node == NULL)
	{
		*errorCode = listIsEmpty;
		return NULL;
	}
	return node->next;
}

void printList(Node* list)
{
	Node* current = list;
	while (current != NULL)
	{
		printf("%s - %s\n", current->name, current->phoneNumber);
		current = current->next;
	}
}

ListErrorCode clearList(Node** list) {
	if (*list == NULL)
	{
		return listIsEmpty;
	}

	while ((*list) != NULL)
	{
		Node* trash = *list;
		*list = (*list)->next;
		free(trash->name);
		free(trash->phoneNumber);
		free(trash);
	}
	return okList;
}

ListErrorCode changeNextNode(Node** node, Node* changeValue)
{
	(*node)->next = changeValue;
}

char* getField(Node* node, int gettingField)
{
	if (gettingField == 1)
	{
		return node->name;
	}
	else
	{
		return node->phoneNumber;
	}
}
