#include <cassert>
#include <iostream>

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <stdlib.h>     /* srand, rand */

#include "hexboard.h"


int main() {
	HexBoard board_hex_test(20, 20, 20);
	std::cout << "------------------------------------------------------------------------------------" << std::endl;
	for (size_t row = 0; row < 20; ++row) {
		for (size_t col = 0; col < 20; ++col) {
			board_hex_test.SetState(row, col, (rand() % 2 == 0));
		}
	}
	for (int i = 0; i < 40; ++i) {
		std::cout << std::endl;
		board_hex_test.TerminalDisplay();
		board_hex_test.NextGeneration();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << std::endl<< "------------------------------------------------------------------------------------" << std::endl;
	}
}
