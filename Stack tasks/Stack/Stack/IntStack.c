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

IntStackErrorCode pushInt(IntStack** const head, const int value)
{
    IntStack* next = (IntStack*)calloc(1, sizeof(IntStack));
    if (next == NULL)
    {
        return outOfMemoryIntStack;
    }
    next->value = value;
    next->previous = *head;
    *head = next;
    return okIntStack;
}

IntStackErrorCode popInt(IntStack** const head)
{
    if (intStackIsEmpty(*head))
    {
        return emptyIntStack;
    }
    IntStack* trash = *head;
    *head = (*head)->previous;
    free(trash);
    return okIntStack;
}

IntStackErrorCode clearIntStack(IntStack** const head)
{
    if (intStackIsEmpty(*head))
    {
        return emptyIntStack;
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

int topInt(IntStack* const head, IntStackErrorCode* const errorCode)
{
    if (intStackIsEmpty(head))
    {
        *errorCode = emptyIntStack;
        return 0;
    }
    return head->value;
}