#include <stdio.h>

void reversePartOfArray(int* array, const int start, const int end)
{
    for (int i = start; i < (start + end + 1) / 2; ++i)
    {
        const int temp = array[i];
        array[i] = array[end - i + start];
        array[end - i + start] = temp;
    }
}

void printReversedArray(const int* const array, const int arrayLength)
{
    printf("Reversed array: ");
    for (int i = 0; i < arrayLength; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void reverseArray(int* array, const int firstSectionLength, const int secondSectionLength)
{
    reversePartOfArray(array, 0, firstSectionLength - 1);
    reversePartOfArray(array, firstSectionLength, firstSectionLength + secondSectionLength - 1);
    reversePartOfArray(array, 0, firstSectionLength + secondSectionLength - 1);
}

int main()
{
    int firstSectionLength = 0, secondSectionLength = 0;

    printf("Enter first section length(positive number less than 1000): ");
    if (scanf_s("%d", &firstSectionLength) != 1 || firstSectionLength <= 0)
    {
        printf("Error input\n");
        return 1;
    }

    printf("Enter second section length(positive number less or equal 1000 - \"first section length\") : ");
    if (scanf_s("%d", &secondSectionLength) != 1 || secondSectionLength <= 0)
    {
        printf("Error input\n");
        return 1;
    }

    int array[1000] = { 0 };
    printf("Enter array of integers with length \"first section length\" + \"second section length\"\n");
    printf("Array: ");
    for (size_t i = 0; i < firstSectionLength + secondSectionLength; ++i)
    {
        if (scanf_s("%d", &array[i]) != 1)
        {
            printf("Error input\n");
            return 1;
        }
    }

    reverseArray(array, firstSectionLength, secondSectionLength);
    printReversedArray(array, firstSectionLength + secondSectionLength);
    
    return 0;
}