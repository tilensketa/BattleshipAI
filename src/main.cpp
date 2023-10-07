#include "Board.h"

#include "Joze.h"

#include <iostream>

int main() {
	const char* data = R"(
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 4 4 4 4 0
0 0 0 0 0 0 0 0 0 0
0 0 2 2 2 0 3 3 3 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 5 5 5 5 5 0 0
0 0 0 0 0 0 0 0 0 0
)";
	Board board(data);
	Print(board.GetData());

	int averageCount = 0;
	for (int i = 0; i < 100; i++)
	{
		Joze joze;
		int count = 1;
		while (true) {
			//std::cout << "Attempt: " << count << std::endl;
			int pos = joze.TakeShot();
			Status status = board.GetStatus(pos);
			joze.Update(pos, status);
			//Print(joze.GetData());
			if (joze.CheckBreak()) {
				std::cout << "Game ended in: " << count << std::endl;
				break;
			}
			count++;
		}
		//std::cin.get();
		averageCount += count;
	}
	averageCount /= 100;
	std::cout << "Average count: " << averageCount << std::endl;
}