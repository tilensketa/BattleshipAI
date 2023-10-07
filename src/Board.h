#pragma once

#include <iostream>

enum Status {
	Sea,
	Unknown,
	Carrier,
	Battleship,
	Destroyer,
	Submarine,
	PatrolBoat
};

class Board {
public:
	Board(const char* boardInfo);

	const Status GetStatus(int pos) const;
    const Status(&GetData())[10][10]{
        return m_Data;
    }
private:
	static const int m_Rows = 10;
	static const int m_Cols = 10;
	Status m_Data[m_Rows][m_Cols];
};

inline static void Print(const Status data[10][10]) {
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            switch (data[x][y])
            {
            case Status::Unknown:
                std::cout << ". ";
                break;
            case Status::Sea:
                std::cout << "+ ";
                break;
            case Status::PatrolBoat:
                std::cout << "P ";
                break;
            case Status::Submarine:
                std::cout << "S ";
                break;
            case Status::Destroyer:
                std::cout << "D ";
                break;
            case Status::Battleship:
                std::cout << "B ";
                break;
            case Status::Carrier:
                std::cout << "C ";
                break;
            }
        }
        std::cout << "" << std::endl;
    }
    std::cout << "____________________" << std::endl;
}