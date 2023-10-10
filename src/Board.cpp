#include "Board.h"

#include "Utils.h"

#include <iostream>
#include <sstream>
#include <vector>

Board::Board(const char* boardInfo) {
    std::istringstream iss(boardInfo);

    std::string line;
    int i = 0;
    while (std::getline(iss, line)) {
        std::istringstream lineStream(line);
        std::vector<Status> row;

        int value;
        while (lineStream >> value) {
            Vec2 xy = posToXY(i, ROWS, COLS);
            int x = xy.X;
            int y = xy.Y;
            //std::cout << i << "/ " << x << ", " << y << ": " << value << std::endl;
            Status cellInfo;
            switch (value)
            {
            case 0:
                cellInfo = Status::Sea;
                break;
            case 1:
                cellInfo = Status::PatrolBoat;
                break;
            case 2:
                cellInfo = Status::Submarine;
                break;
            case 3:
                cellInfo = Status::Destroyer;
                break;
            case 4:
                cellInfo = Status::Battleship;
                break;
            case 5:
                cellInfo = Status::Carrier;
                break;
            default:
                cellInfo = Status::Carrier;
                ASSERT;
            }
            m_Data.Data[x][y] = cellInfo;
            row.push_back(cellInfo);
            i++;
        }
    }
}

const Status Board::GetStatus(int pos) const {
    Vec2 xy = posToXY(pos, ROWS, COLS);
    return m_Data.Data[xy.X][xy.Y];
}