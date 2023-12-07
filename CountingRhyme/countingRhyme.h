#pragma once

// Read the number of warriors and the number of each warrior killed
int readData(int* numberOfWarriors, int* needTokillEvery);

// Count position of last survived warrior
int countPositionOfLastWarrior(const int numberOfWarriors, const int needTokillEvery);