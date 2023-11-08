#include "Gramatica.h"

int main() {
	Gramatica gramatica;
	std::ifstream fin{ "input.txt" };
	if (!fin.is_open()) {
		std::cerr << "Could not open file!\n";
		return 1;
	}
	fin >> gramatica;
	std::cout << gramatica;

	gramatica.verificare();

	gramatica.generare(7);
	fin.close();
}