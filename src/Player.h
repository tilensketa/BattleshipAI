#pragma once

#include "Board.h"

class Player {
public:
	Player();
	virtual int TakeShot() = 0;
	void Update(int position, Status status) {
		int x = position / m_Rows;
		int y = position % m_Cols;
		m_Data[x][y] = status;
	}
	const Status(&GetData())[10][10]{
		return m_Data;
	}
protected:
	static const int m_Rows = 10;
	static const int m_Cols = 10;
	Status m_Data[m_Rows][m_Cols];
};

Player::Player() {
    for (int x = 0; x < m_Rows; x++) {
        for (int y = 0; y < m_Cols; y++) {
			m_Data[x][y] = Status::Unknown;
        }
    }
}