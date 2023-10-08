#pragma once

#include <iostream>

#define ROWS 10
#define COLS 10

enum Status {
	Sea,
	Unknown,
	Carrier,
	Battleship,
	Destroyer,
	Submarine,
	PatrolBoat
};

struct Info {
    Status Data[ROWS][COLS];

    Info() {
        for (int x = 0; x < ROWS; x++) {
            for (int y = 0; y < COLS; y++) {
                Data[x][y] = Status::Sea;
            }
        }
    }

    bool operator== (Info other) {
        for (int x = 0; x < ROWS; x++) {
            for (int y = 0; y < COLS; y++) {
                if (Data[x][y] != other.Data[x][y]) {
                    return false;
                }
            }
        }
        return true;
    }
};

struct HeatMap {
    int Data[ROWS][COLS];

    HeatMap() {
        for (int x = 0; x < ROWS; x++) {
            for (int y = 0; y < COLS; y++) {
                Data[x][y] = 0;
            }
        }
    }
    void Reset() {
        for (int x = 0; x < ROWS; x++) {
            for (int y = 0; y < COLS; y++) {
                Data[x][y] = 0;
            }
        }
    }
};

class Board {
public:
	Board(const char* boardInfo);

	const Status GetStatus(int pos) const;
    const Status(&GetData())[ROWS][COLS]{
        return m_Data;
    }
private:
	Status m_Data[ROWS][COLS];
};