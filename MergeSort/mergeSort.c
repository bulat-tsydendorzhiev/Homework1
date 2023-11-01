#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "mergeSort.h"
#include "list.h"

void split(Node* list, Node** left, Node** right)
{
	ListErrorCode errorCode = okList;
	Node* fast = NULL;
	Node* slow = NULL;

	slow = list;
	fast = getNextNode(list, &errorCode);

	while (fast != NULL) {
		fast = getNextNode(fast, &errorCode);
		if (fast != NULL) {
			fast = getNextNode(fast, &errorCode);
			slow = getNextNode(slow, &errorCode);
		}
	}

	(*left) = list;
	(*right) = getNextNode(slow, &errorCode);
	changeNextNode(&slow, NULL);
}

Node* merge(Node* left, Node* right, const int sortBy)
{
	if (left == NULL)
	{
		return right;
	}

	if (right == NULL)
	{
		return left;
	}

	ListErrorCode errorCode = okList;
	Node* mergedList = NULL;

	if (strcmp(getField(left, sortBy), getField(right, sortBy)) <= 0)
	{
		mergedList = left;
		changeNextNode(&mergedList, merge(getNextNode(left, &errorCode), right, sortBy));
	}
	else
	{
		mergedList = right;
		changeNextNode(&mergedList, merge(left, getNextNode(right, &errorCode), sortBy));
	}

	return mergedList;
}

ListErrorCode mergeSort(Node** list, const int sortBy)
{
	Node* head = *list;
	Node* left = NULL;
	Node* right = NULL;

	// Check for emptiness of list
	const ListErrorCode empty = okList;
	Node* nextNode = getNextNode(*list, &empty);
	if (empty || nextNode == NULL)
	{
		return listIsEmpty;
	}

	split(head, &left, &right);

	mergeSort(&right, sortBy);
	mergeSort(&left, sortBy);

	*list = merge(left, right, sortBy);
	return okList;
}
