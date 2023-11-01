#pragma once

#include "list.h"

// Function to split list on two parts
void split(Node* list, Node** left, Node** right);

// Function to merge parts in one
Node* merge(Node* left, Node* right, const int sortBy);

// Function to sort list
ListErrorCode mergeSort(Node** list, const int sortBy);
