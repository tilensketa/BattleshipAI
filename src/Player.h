#pragma once

#include "Board.h"
#include "Utils.h"

class Player {
public:
	Player();
	virtual int TakeShot() = 0;
	/*void Update(int position, Status status) {
		Vec2 xy = posToXY(position, ROWS, COLS);
		int x = xy.X;
		int y = xy.Y;
		m_Data[x][y] = status;
	}*/
	const Status(&GetData())[ROWS][COLS]{
		return m_Data;
	}
protected:
	Status m_Data[ROWS][COLS];
};

Player::Player() {
    for (int x = 0; x < ROWS; x++) {
        for (int y = 0; y < COLS; y++) {
			m_Data[x][y] = Status::Unknown;
        }
    }
}