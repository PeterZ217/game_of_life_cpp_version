#include <cassert>
#include <iostream>

#include "cell.h"

int main() {
	Cell test = Cell();
	std::cout << "state: " << test.GetState() << std::endl;
}
