#pragma once

#include "Player.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <numeric>
#include <vector>

struct Change {
	int X;
	int Y;
	Status Stat;
};

class Joze : public Player {
public:
	Joze();
	virtual int TakeShot() override;
	bool CheckBreak();
	const std::vector<Info>& GetPosibilities(Status ship);
	const HeatMap& GetHeatMap(Status ship);
	void RecalculateAllPosibilities();
	void RecalculatePosibilities(Status ship);
	void RecalculatePosibilities();
	void Update(int pos, Status status);
	void GenerateAllHeatMaps();
	void GenerateAllPosibilities();
	void PrintShips();
private:
	int RandomShot();
	int HeatMapShot();
	void CalculateShips();
	void GeneratePosibilities(Status ship);
	void GenerateHeatMap(Status ship);
private:
	bool m_Ships[5] = { false, false, false, false, false };
	int m_PatrolBoat = 0;
	int m_Submarine = 0;
	int m_Destroyer = 0;
	int m_Battleship = 0;
	int m_Carrier = 0;

	std::vector<Info> m_PatrolBoatPosibilities;
	std::vector<Info> m_SubmarinePosibilities;
	std::vector<Info> m_DestroyerPosibilities;
	std::vector<Info> m_BattleshipPosibilities;
	std::vector<Info> m_CarrierPosibilities;

	HeatMap m_PatrolBoatHeatMap;
	HeatMap m_SubmarineHeatMap;
	HeatMap m_DestroyerHeatMap;
	HeatMap m_BattleshipHeatMap;
	HeatMap m_CarrierHeatMap;
	HeatMap m_AllShipHeatMap;

	Change m_RecentChange;
};

inline Joze::Joze() {
	GenerateAllPosibilities();
	GenerateAllHeatMaps();
}

inline int Joze::TakeShot() {
	return HeatMapShot();
	//return RandomShot();
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
	int upperBound = ROWS * COLS - 1;
	int lowerBound = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distr(lowerBound, upperBound);
	while (!valid) {
		int randomValue = distr(gen);
		Vec2 xy = posToXY(randomValue, ROWS, COLS);
		int x = xy.X;
		int y = xy.Y;
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
	for (int x = 0; x < ROWS; x++) {
		for (int y = 0; y < COLS; y++) {
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
				case Status::Sea:
					break;
				case Status::Unknown:
					break;
				default:
					ASSERT;
			}
		}
	}
}

inline void Joze::RecalculateAllPosibilities() {
	if (!m_Ships[0]) {
		RecalculatePosibilities(Status::PatrolBoat);
	}
	else {
		m_PatrolBoatPosibilities.clear();
	}
	if (!m_Ships[1]) {
		RecalculatePosibilities(Status::Submarine);
	}
	else {
		m_SubmarinePosibilities.clear();
	}
	if (!m_Ships[2]) {
		RecalculatePosibilities(Status::Destroyer);
	}
	else {
		m_DestroyerPosibilities.clear();
	}
	if (!m_Ships[3]) {
		RecalculatePosibilities(Status::Battleship);
	}
	else {
		m_BattleshipPosibilities.clear();
	}
	if (!m_Ships[4]) {
		RecalculatePosibilities(Status::Carrier);
	}
	else {
		m_CarrierPosibilities.clear();
	}
}

inline void Joze::Update(int pos, Status status) {
	Vec2 xy = posToXY(pos, ROWS, COLS);
	int x = xy.X;
	int y = xy.Y;
	m_Data[x][y] = status;

	m_RecentChange.X = x;
	m_RecentChange.Y = y;
	m_RecentChange.Stat = status;
}

int Joze::HeatMapShot() {

	// Create a vector containing integers from 0 to 100
	std::vector<int> numbers(101);
	std::iota(numbers.begin(), numbers.end(), 0); // Fill the vector with 0 to 100

	// Shuffle the vector using a random engine
	std::random_device rd;
	std::mt19937 rng(rd());
	std::shuffle(numbers.begin(), numbers.end(), rng);

	int highest = 0;
	int pos = 0;

	for (int number : numbers) {
		Vec2 xy = posToXY(number, ROWS, COLS);
		int x = xy.X;
		int y = xy.Y;
		if (m_Data[x][y] == Status::Unknown) {
			int value = m_AllShipHeatMap.Data[x][y];
			if (value > highest) {
				highest = value;
				pos = number;
			}
		}
	}
	return pos;
}

void Joze::GeneratePosibilities(Status ship) {
	int size = 0;
	std::vector<Info>* posibilitiesPtr = nullptr;
	switch (ship) {
		case Carrier:
			size = 5;
			posibilitiesPtr = &m_CarrierPosibilities;
			break;
		case Battleship:
			size = 4;
			posibilitiesPtr = &m_BattleshipPosibilities;
			break;
		case Destroyer:
			size = 3;
			posibilitiesPtr = &m_DestroyerPosibilities;
			break;
		case Submarine:
			size = 3;
			posibilitiesPtr = &m_SubmarinePosibilities;
			break;
		case PatrolBoat:
			size = 2;
			posibilitiesPtr = &m_PatrolBoatPosibilities;
			break;
		default:
			ASSERT;
	}

	// Horizontal
	int x = 0;
	while (x < ROWS) {
		int y = 0;
		while (y + (size - 1) < COLS) {
			Info posibility;
			for (int i = 0; i < size; i++) {
				posibility.Data[x][y+i] = ship;
			}
			posibilitiesPtr->push_back(posibility);
			y++;
		}
		x++;
	}
	// Vertical
	int y = 0;
	while (y < COLS) {
		int x = 0;
		while (x + (size - 1) < ROWS) {
			Info posibility;
			for (int i = 0; i < size; i++) {
				posibility.Data[x + i][y] = ship;
			}
			posibilitiesPtr->push_back(posibility);
			x++;
		}
		y++;
	}
}

void Joze::GenerateHeatMap(Status ship) {
	HeatMap* heatMapPtr = nullptr;
	std::vector<Info>* posibilitiesPtr = nullptr;
	switch (ship) {
		case Carrier:
			heatMapPtr = &m_CarrierHeatMap;
			posibilitiesPtr = &m_CarrierPosibilities;
			break;
		case Battleship:
			heatMapPtr = &m_BattleshipHeatMap;
			posibilitiesPtr = &m_BattleshipPosibilities;
			break;
		case Destroyer:
			heatMapPtr = &m_DestroyerHeatMap;
			posibilitiesPtr = &m_DestroyerPosibilities;
			break;
		case Submarine:
			heatMapPtr = &m_SubmarineHeatMap;
			posibilitiesPtr = &m_SubmarinePosibilities;
			break;
		case PatrolBoat:
			heatMapPtr = &m_PatrolBoatHeatMap;
			posibilitiesPtr = &m_PatrolBoatPosibilities;
			break;
		default:
			ASSERT;
	}
	heatMapPtr->Reset();
	int numberOfPosibilities = posibilitiesPtr->size();
	for (int i = 0; i < posibilitiesPtr->size(); i++) {
		std::vector<Info> posibilities = *posibilitiesPtr;
		Info posibility = posibilities[i];
		for (int x = 0; x < ROWS; x++) {
			for (int y = 0; y < COLS; y++) {
				if (posibility.Data[x][y] == ship) {
					int extra = 100 * 1 / numberOfPosibilities;
					heatMapPtr->Data[x][y] += 1 + extra;
				}
			}
		}
	}
}

const std::vector<Info>& Joze::GetPosibilities(Status ship) {
	switch (ship)
	{
		case Carrier:
			return m_CarrierPosibilities;
			break;
		case Battleship:
			return m_BattleshipPosibilities;
			break;
		case Destroyer:
			return m_DestroyerPosibilities;
			break;
		case Submarine:
			return m_SubmarinePosibilities;
			break;
		case PatrolBoat:
			return m_PatrolBoatPosibilities;
			break;
		default:
			ASSERT;
	}
}

const HeatMap& Joze::GetHeatMap(Status ship) {
	switch (ship)
	{
	case Unknown:
		return m_AllShipHeatMap;
		break;
	case Carrier:
		return m_CarrierHeatMap;
		break;
	case Battleship:
		return m_BattleshipHeatMap;
		break;
	case Destroyer:
		return m_DestroyerHeatMap;
		break;
	case Submarine:
		return m_SubmarineHeatMap;
		break;
	case PatrolBoat:
		return m_PatrolBoatHeatMap;
		break;
	default:
		ASSERT;
	}
}

void Joze::RecalculatePosibilities(Status ship) {
	std::vector<Info>* posibilitiesPtr;
	switch (ship)
	{
		case Carrier:
			posibilitiesPtr = &m_CarrierPosibilities;
			break;
		case Battleship:
			posibilitiesPtr = &m_BattleshipPosibilities;
			break;
		case Destroyer:
			posibilitiesPtr = &m_DestroyerPosibilities;
			break;
		case Submarine:
			posibilitiesPtr = &m_SubmarinePosibilities;
			break;
		case PatrolBoat:
			posibilitiesPtr = &m_PatrolBoatPosibilities;
			break;
		default:
			posibilitiesPtr = &m_PatrolBoatPosibilities;
			ASSERT;
	}

	std::vector<Info> infos;
	for (int i = 0; i < posibilitiesPtr->size(); i++) {
		std::vector<Info> posibilities = *posibilitiesPtr;
		Info posibility = posibilities[i];
		int x = m_RecentChange.X;
		int y = m_RecentChange.Y;
		Status target = m_RecentChange.Stat;
		if (posibility.Data[x][y] == target) {
			infos.push_back(posibility);
		}
	}

	posibilitiesPtr->clear();
	for (const Info& info : infos) {
		posibilitiesPtr->push_back(info);
	}
}

void Joze::RecalculatePosibilities() {
	CalculateShips();

	int x = m_RecentChange.X;
	int y = m_RecentChange.Y;
	Status target = m_RecentChange.Stat;
	if (target == Status::Sea) {
		RecalculateAllPosibilities();
		return;
	}
	std::vector<Info>* posibilitiesPtr;
	switch (target)
	{
		case Carrier:
			if (m_Ships[4] == true) {
				m_CarrierPosibilities.clear();
				return;
			}
			posibilitiesPtr = &m_CarrierPosibilities;
			break;
		case Battleship:
			if (m_Ships[3] == true) {
				m_BattleshipPosibilities.clear();
				return;
			}
			posibilitiesPtr = &m_BattleshipPosibilities;
			break;
		case Destroyer:
			if (m_Ships[2] == true) {
				m_DestroyerPosibilities.clear();
				return;
			}
			posibilitiesPtr = &m_DestroyerPosibilities;
			break;
		case Submarine:
			if (m_Ships[1] == true) {
				m_SubmarinePosibilities.clear();
				return;
			}
			posibilitiesPtr = &m_SubmarinePosibilities;
			break;
		case PatrolBoat:
			if (m_Ships[0] == true) {
				m_PatrolBoatPosibilities.clear();
				return;
			}
			posibilitiesPtr = &m_PatrolBoatPosibilities;
			break;
		default:
			posibilitiesPtr = &m_PatrolBoatPosibilities;
			return;
	}

	std::vector<Info> infos;
	for (int i = 0; i < posibilitiesPtr->size(); i++) {
		std::vector<Info> posibilities = *posibilitiesPtr;
		Info posibility = posibilities[i];
		if (posibility.Data[x][y] == target) {
			infos.push_back(posibility);
		}
	}

	posibilitiesPtr->clear();
	for (const Info& info : infos) {
		posibilitiesPtr->push_back(info);
	}
}

void Joze::GenerateAllHeatMaps() {
	GenerateHeatMap(Status::PatrolBoat);
	GenerateHeatMap(Status::Submarine);
	GenerateHeatMap(Status::Destroyer);
	GenerateHeatMap(Status::Battleship);
	GenerateHeatMap(Status::Carrier);

	// Generate all ship heat map
	m_AllShipHeatMap.Reset();
	for (int i = 0; i < 5; i++) {
		HeatMap heatMap;
		switch (i)
		{
			case 0:
				heatMap = m_PatrolBoatHeatMap;
				break;
			case 1:
				heatMap = m_SubmarineHeatMap;
				break;
			case 2:
				heatMap = m_DestroyerHeatMap;
				break;
			case 3:
				heatMap = m_BattleshipHeatMap;
				break;
			case 4:
				heatMap = m_CarrierHeatMap;
				break;
			default:
				ASSERT;
		}

		for (int x = 0; x < ROWS; x++) {
			for (int y = 0; y < COLS; y++) {
				m_AllShipHeatMap.Data[x][y] += heatMap.Data[x][y];
			}
		}
	}
}

void Joze::GenerateAllPosibilities() {
	GeneratePosibilities(Status::PatrolBoat);
	GeneratePosibilities(Status::Submarine);
	GeneratePosibilities(Status::Destroyer);
	GeneratePosibilities(Status::Battleship);
	GeneratePosibilities(Status::Carrier);
}

void Joze::PrintShips() {
	for (int i = 0; i < 5; i++) {
		if (m_Ships[i] == true)
			std::cout << "sinked ";
		else
			std::cout << "floating ";
	}
	std::cout << std::endl;
}