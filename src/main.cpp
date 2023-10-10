#include "Board.h"

#include "Joze.h"

#include <iostream>

int main() {
	const char* data10 = R"(
0 0 0 0 0 0 0 0 0 0
3 3 3 0 0 0 0 0 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 5 5 5 5 5
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 2
0 0 0 0 0 0 0 0 0 2
0 0 0 0 4 4 4 4 0 2
)";

	Board board(data10);
	Print(board.GetData(), -1);

	int averageCount = 0;
	int lowestCount = ROWS * COLS;
	int largestCount = 0;

	bool heatMaps = true;
	bool heatMap = true;

	bool autoMode = false;

	int numberOfGames = 100;
	for (int i = 0; i < numberOfGames; i++) {
		Joze joze;
		int count = 1;
		while (!joze.CheckBreak()) {
			if (!autoMode) {
				std::cout << "Attempt: " << count << std::endl;
				if (heatMaps) {
					std::cout << "Number of posibilities PatrolBoat: " << joze.GetPosibilities(Status::PatrolBoat).size() << std::endl;
					ViewHeatMap(joze.GetHeatMap(Status::PatrolBoat));
					std::cout << "Number of posibilities Submarine: " << joze.GetPosibilities(Status::Submarine).size() << std::endl;
					ViewHeatMap(joze.GetHeatMap(Status::Submarine));
					std::cout << "Number of posibilities Destroyer: " << joze.GetPosibilities(Status::Destroyer).size() << std::endl;
					ViewHeatMap(joze.GetHeatMap(Status::Destroyer));
					std::cout << "Number of posibilities Battleship: " << joze.GetPosibilities(Status::Battleship).size() << std::endl;
					ViewHeatMap(joze.GetHeatMap(Status::Battleship));
					std::cout << "Number of posibilities Carrier: " << joze.GetPosibilities(Status::Carrier).size() << std::endl;
					ViewHeatMap(joze.GetHeatMap(Status::Carrier));
				}
				if (heatMap) {
					std::cout << "All ship HeatMap" << std::endl;
					ViewHeatMap(joze.GetHeatMap(Status::Unknown));
				}
			}
			int pos = joze.TakeShot();
			Status status = board.GetStatus(pos);
			joze.Update(pos, status);
			joze.RecalcAll();
			joze.GenerateAllHeatMaps();
			if (!autoMode) {
				Print(joze.GetData(), pos);
				std::cin.get();
			}
			count++;
		}
		if (autoMode) {
			int length = numberOfGames / 20;
			if (i % length == 0) {
				std::cout << ".";
			}
		}
		averageCount += count;
		if (count < lowestCount)
			lowestCount = count;
		if (count > largestCount)
			largestCount = count;
	}
	averageCount /= numberOfGames;
	std::cout << std::endl;
	std::cout << "Average count: " << averageCount << std::endl;
	std::cout << "Lowest count: " << lowestCount << std::endl;
	std::cout << "Largest count: " << largestCount << std::endl;
}