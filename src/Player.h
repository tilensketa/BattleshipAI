#pragma once

#include "Board.h"
#include "Utils.h"

class Player {
public:
	Player();
	virtual int TakeShot() = 0;

	const Info& GetData() const { return m_Data; }
protected:
	Info m_Data;
};

Player::Player() {
    for (int x = 0; x < ROWS; x++) {
        for (int y = 0; y < COLS; y++) {
			m_Data.Data[x][y] = Status::Unknown;
        }
    }
}