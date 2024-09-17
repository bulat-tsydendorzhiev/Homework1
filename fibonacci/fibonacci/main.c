#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define TESTS_PASSED -1
#define SUCCESS 0

int recursiveFibonacci(const int number, bool* const errorOccured)
{
    if (number < 0)
    {
        *errorOccured = true;
        return -1;
    }
    if (number == 0)
    {
        return 0;
    }
    if (number <= 2)
    {
        return 1;
    }
    return recursiveFibonacci(number - 1, errorOccured) + recursiveFibonacci(number - 2, errorOccured);
}

int iterativeFibonacci(const int number, bool* const errorOccured)
{
    if (number < 0)
    {
        *errorOccured = true;
        return -1;
    }
    
    int currentNumber = 0;
    int previousNumber = 1;
    for (size_t i = 0; i < number; ++i)
    {
        currentNumber = currentNumber + previousNumber;
        previousNumber = currentNumber - previousNumber;
    }
    return currentNumber;
}

bool runTestingFunction(const int *const function(const int, bool* const))
{
    const int expected[] = { -1, 0, 1, 1, 2, 3, 5, 8 };
    const bool expectedErrors[] = { true, false, false, false, false, false, false, false };
    const int numberOfTests = sizeof(expected) / sizeof(expected[0]);
    for (size_t i = 0; i < numberOfTests; ++i)
    {
        bool errorInput = false;
        const int tempResult = function(i - 1, &errorInput);
        if (tempResult != expected[i] || errorInput != expectedErrors[i])
        {
            return false;
        }
    }
    return true;
}

bool runTests(void)
{
    const bool recursiveFibonacciTestPassed = runTestingFunction(recursiveFibonacci);
    if (!recursiveFibonacciTestPassed)
    {
        return false;
    }

    const bool iterativeFibonacciTestPassed = runTestingFunction(iterativeFibonacci);
    if (!iterativeFibonacciTestPassed)
    {
        return false;
    }
    return true;
}

void timeCompare(void)
{
    bool errorInput = false;
    for (int i = 0; i < 50; ++i)
    {
        clock_t start = clock();
        recursiveFibonacci(i, &errorInput);
        clock_t end = clock();
        const double timeForRecursive = ((double)(end - start)) / CLOCKS_PER_SEC;

        start = clock();
        iterativeFibonacci(i, &errorInput);
        end = clock();
        const double timeForIterative = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Fibonacci number = %d | iterative method time = %lf | recursive method time = %lf\n", i, timeForIterative, timeForRecursive);
    }
}

int main()
{
    const bool testsPassed = runTests();
    if (!testsPassed)
    {
        return TESTS_PASSED;
    }

    // time compare in interactive mode
    timeCompare();
    return SUCCESS;
}