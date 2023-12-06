#pragma once

#include <stdbool.h>

// Algorithm of cities distribution
void distributeCities(size_t** graph, size_t numberOfCities, size_t** states, size_t numberOfCapitals, bool* visited);

// Print states with their cities
void printStates(const size_t* const* const states, const size_t numberOfStates);
