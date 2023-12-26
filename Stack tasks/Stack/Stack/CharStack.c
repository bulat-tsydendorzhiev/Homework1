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

CharStackErrorCode pushChar(CharStack** const head, const char value)
{
    CharStack* next = (CharStack*)calloc(1, sizeof(CharStack));
    if (next == NULL)
    {
        return outOfMemoryCharStack;
    }
    next->value = value;
    next->previous = *head;
    *head = next;
    return okCharStack;
}

CharStackErrorCode popChar(CharStack** const head)
{
    if (*head == NULL)
    {
        return emptyCharStack;
    }
    CharStack* trash = *head;
    *head = (*head)->previous;
    free(trash);
    return okCharStack;
}

CharStackErrorCode clearCharStack(CharStack** const head)
{
    if (head == NULL || *head == NULL)
    {
        return emptyCharStack;
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

char topChar(CharStack* const head, CharStackErrorCode* const errorCode)
{
    if (head == NULL)
    {
        *errorCode = emptyCharStack;
        return '\0';
    }
    return head->value;
}