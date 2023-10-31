#pragma once

// Function to write the number of warriors and the number of each warrior killed
int writeData(int* numberOfWarriors, int* needTokillEvery);

// Function to count position of last survived warrior
int getPositionOfLastWarrior(const int numberOfWarriors, const int needTokillEvery);