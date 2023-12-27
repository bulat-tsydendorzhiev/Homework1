#include <stdio.h>
#include <string.h>

#include "substringSearch.h"

#define BASE 13
#define MOD 991

static size_t calculateHash(const char* const string, const size_t length)
{
    size_t hash = 0;
    for (size_t i = 0; i < length; ++i)
    {
        hash = (BASE * hash + string[i]) % MOD;
    }
    return hash;
}

int substringSearch(const char* const string, const char* const substring)
{
    if (string == NULL || substring == NULL)
    {
        return -1;
    }

    const size_t stringLength = strlen(string);
    const size_t substringLength = strlen(substring);

    const size_t substringHash = calculateHash(substring, substringLength);
    size_t currentHash = calculateHash(string, substringLength);
    size_t preMaxDegree = 1;
    for (size_t i = 0; i < substringLength - 1; ++i)
    {
        preMaxDegree = preMaxDegree * BASE;
    }

    for (size_t i = 0; i <= stringLength - substringLength; ++i)
    {
        if (currentHash == substringHash)
        {
            for (size_t j = 0; j < substringLength; ++j)
            {
                if (substring[j] != string[i + j])
                {
                    break;
                }
                if (j + 1 == substringLength)
                {
                    return i;
                }
            }
        }
        currentHash = currentHash - (string[i] * preMaxDegree) % MOD;
        currentHash = ((currentHash + MOD) % MOD * BASE + string[i + substringLength]) % MOD;
    }
    return -1;
}