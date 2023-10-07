#pragma once

#include "Player.h"

#include <iostream>

class Joze : public Player {
public:
	virtual int TakeShot() override;
private:
	int RandomShot();
};

inline int Joze::TakeShot() {
	return RandomShot();
}

inline int Joze::RandomShot() {
	bool valid = false;
	while (!valid) {
		int upperBound = m_Rows * m_Cols - 1;
		int lowerBound = 0;
		int randomValue = std::rand() % (upperBound - lowerBound + 1) + lowerBound;
		int x = randomValue / m_Rows;
		int y = randomValue % m_Cols;
		if (m_Data[x][y] == Status::Unknown) {
			return randomValue;
		}
	}
}