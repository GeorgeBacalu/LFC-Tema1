#include "Gramatica.h"
#include <fstream>

int main() {
	Gramatica gramatica;
	std::ifstream fin{ "input.txt" };
	if (!fin.is_open()) {
		std::cerr << "Could not open file!\n";
		return 1;
	}
	fin >> gramatica;
	std::cout << gramatica;
	if (gramatica.verificare())
	{
		std::cout << "Gramatica este valida\n";
		if (gramatica.esteRegulata())
		{
			std::cout << "Gramatica este regulata\n\n";
			gramatica.generare(3);
		}
	}
	fin.close();
}