#include <stdio.h>
#include <stdbool.h>

#include "list.h"
#include "deleteEverySecond.h"

void addElements(List* list, const int* const insertingElements, const int length)
{
    for (size_t i = 0; i < length; ++i)
    {
        add(list, insertingElements[i]);
    }
}

bool isSimilar(List* list, const int* const expected, const int length)
{
    for (size_t i = 0; i < length; ++i)
    {
        if (!contains(list, expected[i]))
        {
            return false;
        }
    }
    return true;
}

bool test(void)
{
    const int insertingValues[] = {1,2,3,4,5,6};
    const int length = sizeof(insertingValues) / sizeof(insertingValues[0]);
    const int expected[] = { 1,3,5 };
    const int lengthExpected = sizeof(expected) / sizeof(expected[0]);
    List* list = createList();
    if (list == NULL)
    {
        return true;
    }

    addElements(list, insertingValues, length);
    deleteEverySecond(list);

    if (!isSimilar(list, expected, lengthExpected))
    {
        return true;
    }
    deleteList(&list);
    return false;
}

int main()
{
    const bool testError = test();
    if (testError)
    {
        printf("Test failed\n");
        return testError;
    }

}