#pragma once

#include <stdbool.h>

#include "list.h"

typedef enum
{
	testsPassed,
	testErrorCode1,
	testErrorCode2,
	testErrorCode3,
	testErrorCode4,
	testErrorCode5
} TestErrorCode;

// Function to compare expected results with obtained results
bool isSimilar(Node* list, Node* expectedResults, int gettingField);

// Function for tests for checking correct execution of the program
TestErrorCode tests(void);
