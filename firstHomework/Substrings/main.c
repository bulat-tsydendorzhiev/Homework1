#include <stdio.h>
#include <stdbool.h>

#define STRING_LENGTH_LIMIT 100

int main()
{
    char string[STRING_LENGTH_LIMIT] = "";
    char substring[STRING_LENGTH_LIMIT] = "";

    printf("Enter a string not exceeding %d characters in length: ", STRING_LENGTH_LIMIT);
    scanf_s("%s", string, STRING_LENGTH_LIMIT);
    printf("Enter a substring not exceeding %d characters in length: ", STRING_LENGTH_LIMIT);
    scanf_s("%s", substring, STRING_LENGTH_LIMIT);

    size_t numberOfOccurrences = 0;
    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        bool substringEntryCheck = true;
        for (size_t j = 0; substring[j] != '\0'; ++j)
        {
            if (string[i + j] != substring[j])
            {                                 
                substringEntryCheck = false;
                break;                        
            }
        }
        if (substringEntryCheck)
        {
            ++numberOfOccurrences;
        }
    }
    printf("Number of occurrences = %Iu\n", numberOfOccurrences);
    return 0;
}