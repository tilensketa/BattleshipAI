#pragma once

#include "Player.h"

#include <iostream>
#include <random>

class Joze : public Player {
public:
	virtual int TakeShot() override;
	bool CheckBreak();
private:
	int RandomShot();
	void CalculateShips();
private:
	bool m_Ships[5] = { false, false, false, false, false };
	int m_PatrolBoat = 0;
	int m_Submarine = 0;
	int m_Destroyer = 0;
	int m_Battleship = 0;
	int m_Carrier = 0;
};

inline int Joze::TakeShot() {
	return RandomShot();
}

inline bool Joze::CheckBreak() {
	CalculateShips();
	for (int i = 0; i < 5; i++) {
		if (m_Ships[i] == false)
			return false;
	}
	return true;
}

inline int Joze::RandomShot() {
	bool valid = false;
	int upperBound = m_Rows * m_Cols - 1;
	int lowerBound = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distr(lowerBound, upperBound);
	while (!valid) {
		//int randomValue = std::rand() % (upperBound - lowerBound + 1) + lowerBound;
		int randomValue = distr(gen);
		int x = randomValue / m_Rows;
		int y = randomValue % m_Cols;
		if (m_Data[x][y] == Status::Unknown) {
			return randomValue;
		}
	}
}

inline void Joze::CalculateShips() {
	m_PatrolBoat = 0;
	m_Submarine = 0;
	m_Destroyer = 0;
	m_Battleship = 0;
	m_Carrier = 0;
	for (int x = 0; x < m_Rows; x++) {
		for (int y = 0; y < m_Cols; y++) {
			const Status& status = m_Data[x][y];
			switch (status)
			{
				case Status::PatrolBoat:
					m_PatrolBoat++;
					if (m_PatrolBoat == 2)
						m_Ships[0] = true;
					break;
				case Status::Submarine:
					m_Submarine++;
					if (m_Submarine == 3)
						m_Ships[1] = true;
					break;
				case Status::Destroyer:
					m_Destroyer++;
					if (m_Destroyer == 3)
						m_Ships[2] = true;
					break;
				case Status::Battleship:
					m_Battleship++;
					if (m_Battleship == 4)
						m_Ships[3] = true;
					break;
				case Status::Carrier:
					m_Carrier++;
					if (m_Carrier == 5)
						m_Ships[4] = true;
					break;
			}
		}
	}
}