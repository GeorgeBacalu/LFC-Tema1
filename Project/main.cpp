#include "Gramatica.h"
#include "AutomatFinit.h"
#include <fstream>

int main() {
	Gramatica gramatica;
	std::ifstream fin{ "input.txt" };
	if (!fin.is_open()) {
		std::cerr << "Could not open file!\n";
		return 1;
	}
	AutomatFinit automatFinit;
	std::ifstream fin2{ "inputAutomatFinit.txt" };
	if (!fin2.is_open()) {
		std::cerr << "Could not open file!\n";
		return 1;
	}

	int optiune;
	std::string cuvant;
	fin >> gramatica;
	do
	{
		std::cout << "Meniu comenzi:\n";
		std::cout << "0. Iesire\n";
		std::cout << "1. Afisarea gramaticii G\n";
		std::cout << "2. Generarea unui numar n de cuvinte in gramatica G\n";
		std::cout << "3. Obtinerea automatului echivalent cu gramatica G si afisarea acestuia\n";
		std::cout << "4. Verificarea daca un cuvant dat este acceptat de automatul finit\n";
		std::cout << "5. Generarea unui cuvant in G + verificarea daca acesta este acceptat de automatul finit\n";
		std::cout << "Alegeti o optiune: ";
		std::cin >> optiune;
		switch (optiune)
		{
		case 0:
			break;
		case 1:
			std::cout << "Se afiseaza gramatica:\n" << gramatica;
			break;
		case 2:
			int nrCuvinte;
			std::cout << "Introdu numarul de cuvinte pe care doresti sa le generezi: ";
			std::cin >> nrCuvinte;
			if (gramatica.verificare())
			{
				gramatica.generare(nrCuvinte);
			}
			break;
		case 3:
			if (gramatica.verificare())
			{
				std::cout << "Gramatica este valida\n";
				if (gramatica.esteRegulata())
				{
					std::cout << "Gramatica este regulata\n\n";
					std::cout << "Rezultat transformare gramatica in automat finit:\n" << gramatica.transformaInAutomatFinit();
				}
			}
			break;
		case 4:
			std::cout << "Introdu cuvantul pe care doresti sa-l verifici: ";
			std::cin >> cuvant;
			if (automatFinit.verificareCuvant(automatFinit.getStareInitiala(), cuvant))
				std::cout << "Cuvantul " << cuvant << " este acceptat de automat\n";
			else
				std::cout << "Cuvantul " << cuvant << " nu este acceptat de automat\n";
			break;
		case 5:
			std::set<std::string> cuvantGeneratSet = gramatica.generare(1);
			std::string cuvantGenerat = *cuvantGeneratSet.begin();
			if (automatFinit.verificareCuvant(automatFinit.getStareInitiala(), cuvantGenerat))
				std::cout << "Cuvantul " << cuvantGenerat << " generat de gramatica este acceptat de automat\n";
			else
				std::cout << "Cuvantul " << cuvantGenerat << " generat de gramatica nu este acceptat de automat\n";
			break;
		}
	}
	while (optiune);
	fin.close();
	fin2.close();
	return 0;
}