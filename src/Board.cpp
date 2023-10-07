#include "Board.h"

#include <iostream>
#include <sstream>
#include <vector>

Board::Board(const char* boardInfo) {
    std::istringstream iss(boardInfo);
    std::vector<std::vector<Status>> parsedData;

    std::string line;
    int i = 0;
    while (std::getline(iss, line)) {
        std::istringstream lineStream(line);
        std::vector<Status> row;

        int value;
        while (lineStream >> value) {
            int x = i / m_Rows;
            int y = i % m_Cols;
            //std::cout << i << "/ " << x << ", " << y << ": " << value << std::endl;
            Status cellInfo;
            switch (value)
            {
                case 0:
                    m_Data[x][y] = Status::Sea;
                    break;
                case 1:
                    m_Data[x][y] = Status::PatrolBoat;
                    break;
                case 2:
                    m_Data[x][y] = Status::Submarine;
                    break;
                case 3:
                    m_Data[x][y] = Status::Destroyer;
                    break;
                case 4:
                    m_Data[x][y] = Status::Battleship;
                    break;
                case 5:
                    m_Data[x][y] = Status::Carrier;
                    break;
            }
            row.push_back(cellInfo);
            i++;
        }
        parsedData.push_back(row);
    }
}

const Status Board::GetStatus(int pos) const {
    int x = pos / m_Rows;
    int y = pos % m_Cols;
    return m_Data[x][y];
}