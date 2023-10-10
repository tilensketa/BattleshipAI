#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>
#include <iomanip>

#define ASSERT assert(false)

struct Vec2 {
    int X;
    int Y;
    Vec2(int x, int y)
        : X(x), Y(y) {}
};

inline Vec2 posToXY(int pos, int rows, int cols) {
    int x = pos / rows;
    int y = pos % cols;
    return Vec2(x, y);
}

#define RED "\033[41m"
#define GREEN "\033[42m"
#define YELLOW "\033[43m"
#define BLUE "\033[44m"
#define MAGENTA "\033[45m"
#define CYAN "\033[46m"
#define WHITE "\033[47m\033[30m"
#define RESET "\033[0m"

#define MAGENTABLACK "\033[45m\033[30m"

static void Print(const Status data[ROWS][COLS], int pos) {
    Vec2 xy = posToXY(pos, ROWS, COLS);
    int xi = xy.X;
    int yi = xy.Y;
    for (int x = 0; x < ROWS; x++) {
        for (int y = 0; y < COLS; y++) {
            if (xi == x && yi == y) {
                std::cout << RED;
            }
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
            std::cout << RESET;
        }
        std::cout << "" << std::endl;
    }
    std::cout << "____________________" << std::endl;
}

static void Print(const Info data) {
    for (int x = 0; x < ROWS; x++) {
        for (int y = 0; y < COLS; y++) {
            switch (data.Data[x][y])
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

static int Range(int value, float delta, int lowest, int largest) {
    if (value == largest)
        return 7;
    else if (value >= lowest && value < lowest + delta)
        return 0;
    else if (value >= lowest + 1 * delta && value < lowest + 2 * delta)
        return 1;
    else if (value >= lowest + 2 * delta && value < lowest + 3 * delta)
        return 2;
    else if (value >= lowest + 3 * delta && value < lowest + 4 * delta)
        return 3;
    else if (value >= lowest + 4 * delta && value < lowest + 5 * delta)
        return 4;
    else if (value >= lowest + 5 * delta && value < lowest + 6 * delta)
        return 5;
    else if (value >= lowest + 6 * delta)
        return 6;
}

static void ViewHeatMap(const HeatMap heatMap) {
    int largest = 0;
    int lowest = 100;
    for (int x = 0; x < ROWS; x++) {
        for (int y = 0; y < COLS; y++) {
            int value = heatMap.Data[x][y];
            if (value > largest) {
                largest = value;
            }
            if (value < lowest) {
                lowest = value;
            }
        }
    }

    int range = largest - lowest;
    float delta = (float)range / 7;

    int numberOfDigits = 3;

    for (int x = 0; x < ROWS; x++) {
        for (int y = 0; y < COLS; y++) {
            int value = heatMap.Data[x][y];
            int rangeNumber = Range(value, delta, lowest, largest);
            switch (rangeNumber)
            {
                case 0:
                    std::cout << WHITE;;
                    break;
                case 1:
                    std::cout << BLUE;
                    break;
                case 2:
                    std::cout << GREEN;
                    break;
                case 3:
                    std::cout << CYAN;
                    break;
                case 4:
                    std::cout << YELLOW;
                    break;
                case 5:
                    std::cout << RED;
                    break;
                case 6:
                    std::cout << MAGENTA;
                    break;
                case 7:
                    std::cout  << MAGENTABLACK;
                    break;
            }
            if (value > 99)
                std::cout << value << RESET;
            else if (value <= 99 && value > 9)
                std::cout << " " << value << RESET;
            else
                std::cout << "  " << value << RESET;
        }
        std::cout << "" << std::endl;
    }
    std::cout << "--------------------" << std::endl;
}

