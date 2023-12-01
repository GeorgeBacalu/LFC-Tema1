#include "Gramatica.h"
#include "AutomatFinit.h"

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

	AutomatFinit automatFinit;
	std::ifstream fin2{ "inputAutomatFinit.txt" };
	if (!fin2.is_open()) {
		std::cerr << "Could not open file!\n";
		return 1;
	}
	fin2 >> automatFinit;
	std::cout << automatFinit;
	automatFinit.verificareAutomat();
	automatFinit.esteDeterminist();

	std:: string cuvant = "abbabaa";
	if(automatFinit.verificareCuvant(automatFinit.getStareInitiala(), cuvant))
		std::cout << "Cuvantul " << cuvant << " este acceptat de automat\n";
	else
		std::cout << "Cuvantul " << cuvant << " nu este acceptat de automat\n";
	
	return 0;
}