#include <stdio.h>
#include <stdbool.h>

void shellSort(int* array, const int length)
{
    for (int step = length / 2; step > 0; step /= 2)
        for (int i = step; i < length; ++i)
        {
            int j = i;
            int temp = array[i];
            for (j; j >= step; j -= step)
            {
                if (temp < array[j - step])
                    array[j] = array[j - step];
                else
                    break;
            }
            array[j] = temp;
        }
}

bool similar(int* array, int* expectedArray, const int length)
{
    for (int i = 0; i < length; ++i)
    {
        if (array[i] != expectedArray[i])
        {
            return false;
        }
    }
    return true;
}

int tests(void)
{
    int testArray1[] = { 5,2,3,4,1 };
    const int length1 = sizeof(testArray1) / sizeof(testArray1[0]);
    shellSort(testArray1, length1);
    const int expectedArray1[] = { 1,2,3,4,5 };
    if (!similar(testArray1, expectedArray1, length1))
    {
        return 1;
    }
    
    int testArray2[] = { -1,-2,-3,-4,-5 };
    const int length2 = sizeof(testArray2) / sizeof(testArray2[0]);
    shellSort(testArray2, length2);
    const int expectedArray2[] = { -5,-4,-3,-2,-1 };
    if (!similar(testArray2, expectedArray2, length2))
    {
        return 2;
    }

    int testArray3[] = { 1,1,1,1,1 };
    const int length3 = sizeof(testArray3) / sizeof(testArray3[0]);
    shellSort(testArray3, length3);
    const int expectedArray3[] = { 1,1,1,1,1 };
    if (!similar(testArray3, expectedArray3, length3))
    {
        return 3;
    }
    return 0;
}

int main(void)
{
    const int errorTest = tests();
    if (errorTest)
    {
        return errorTest;
    }
    return 0;
}