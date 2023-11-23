#include "Gramatica.h"

Gramatica::Gramatica() : m_VN{ {} }, m_VT{ {} }, m_P{ {} }, m_S{ 'S' } {}

Gramatica::Gramatica(const std::set<char>& VN, const std::set<char>& VT, const std::set<Productie>& P, char S) : m_VN{ VN }, m_VT{ VT }, m_P{ P }, m_S{ S } {}

Gramatica::~Gramatica() {}

std::istream& operator>>(std::istream& in, Gramatica& gramatica) 
{
	int nrNeterminale, nrTerminale, nrProductii;
	in >> nrNeterminale;

	for (int i = 0; i < nrNeterminale; i++) 
	{
		char neterminal;
		in >> neterminal;
		gramatica.m_VN.insert(neterminal);
	}

	in >> nrTerminale;

	for (int i = 0; i < nrTerminale; i++) 
	{
		char terminal;
		in >> terminal;
		gramatica.m_VT.insert(terminal);
	}

	in >> gramatica.m_S >> nrProductii;
	std::string stanga, dreapta;

	for (int i = 0; i < nrProductii; i++) 
	{
		in >> stanga >> dreapta;
		gramatica.m_P.emplace(stanga, dreapta);
	}

	gramatica.m_VN.erase('\0'); // Remove null character from m_VN
	gramatica.m_VT.erase('\0'); // Remove null character from m_VT
	std::set<Productie>::iterator it = gramatica.m_P.begin();

	if (!gramatica.m_P.empty())
	{
		gramatica.m_P.erase(it);
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, const Gramatica& gramatica) 
{
	out << "G = ({";

	for (char ch : gramatica.m_VN)
	{
		out << ch << " ";
	}

	out << "}, {";

	for (char ch : gramatica.m_VT)
	{
		out << ch << " ";
	}
	out << "}, " << gramatica.m_S << ", P}\n";

	for (const auto& productie : gramatica.m_P)
	{
		if (!productie.first.empty())
		{
			out << productie.first << "->" << productie.second << "\n\n";
		}
	}
	return out;
}

const std::set<char>& Gramatica::GetVN() const { return m_VN; }

void Gramatica::SetVN(const std::set<char>& VN) { m_VN = VN; }

const std::set<char>& Gramatica::GetVT() const { return m_VT; }

void Gramatica::SetVT(const std::set<char>& VT) { m_VT = VT; }

const std::set<Productie>& Gramatica::GetP() const { return m_P; }

void Gramatica::SetP(const std::set<Productie>& P) { m_P = P; }

char Gramatica::GetS() const { return m_S; }

void Gramatica::SetS(char S) { m_S = S; }

void Gramatica::generare(int nrCuvinte) 
{
	m_cuvinteGenerate.clear(); // Goleste set ul de cuvinte generate
	std::string cuvantGenerat;


	std::random_device rd;
	std::mt19937 eng(rd());
	

	while (m_cuvinteGenerate.size() < nrCuvinte) 
	{
	    cuvantGenerat = std::string(1, m_S); // Pornim de la simbolul de start

		while (true) 
		{
			std::set<std::pair<std::string, std::string>> productiiAplicabile;

			for (const Productie& prod : m_P)
			{
				if (cuvantGenerat.find(prod.first) != std::string::npos) 
				{
					productiiAplicabile.insert(prod);
				}
			}

			if (productiiAplicabile.empty()) 
			{
				m_cuvinteGenerate.insert(cuvantGenerat);
				break;
			}
            
			std::uniform_int_distribution<int> distr(0, productiiAplicabile.size() - 1);
			int indexProductie = distr(eng);



			// Find the selected production using iterators
			auto it = productiiAplicabile.begin();
			std::advance(it, indexProductie);
			const Productie& selectedProd = *it;

			
			//pentru a alege random o pozitie in care se poate aplica o productie
			std::vector<size_t> pozitiiPosibile;
			size_t pozitie = cuvantGenerat.find(selectedProd.first);

			while (pozitie != std::string::npos) 
			{
				pozitiiPosibile.push_back(pozitie);
				pozitie = cuvantGenerat.find(selectedProd.first, pozitie + 1);
			}

			std::uniform_int_distribution<int> distr2(0, pozitiiPosibile.size() - 1);
			int pozitieInlocuire = pozitiiPosibile[distr2(eng)];

			//int pozitieInlocuire = cuvantGenerat.find(selectedProd.first);
			
			std::cout << cuvantGenerat << " => ";
			if(selectedProd.second == "@")
			cuvantGenerat.replace(pozitieInlocuire, selectedProd.first.length(), "");
			else
			cuvantGenerat.replace(pozitieInlocuire, selectedProd.first.length(), selectedProd.second);
		}
		std::cout << cuvantGenerat << "\n\n";
	}

	// Afiseaza cuvintele generate
	//for (const std::string& cuvant : m_cuvinteGenerate) {
	//	std::cout << cuvant << std::endl;
	//}
}

bool Gramatica::verificare()
{
	if (m_VN.empty() || m_VT.empty()) 
	{
		std::cout << "gramatica invalida : VN sau NT sunt vide \n";
		return false;
	}
	// m_VT si m_VN intersectie nula
	for (auto caracter : m_VN)
	{
		if (m_VT.find(caracter) != m_VT.end())
		{
			std::cout << "gramatica invalida : caractere din VN se afla in VT \n";
			return false;
		}
	}
	for (auto caracter : m_VT)
	{
		if (m_VN.find(caracter) != m_VN.end())
		{
			std::cout << "gramatica invalida : caractere din VT se afla in VN \n";
			return false;
		}
	}

	// (2) S în VN
	if (m_VN.find(m_S) == m_VN.end()) 
	{
		std::cout << "gramatica invalida : m_S nu se afla in VN\n";
		return false;
	}


	// fiecare productie sa aiba macar un neterminal in stanga
	bool areNeterminal;
	for (const auto& productie : m_P) 
	{
		areNeterminal = false;

		for (auto caracter : m_VN)
		{
			if (productie.first.find(caracter) != std::string::npos)
			{
				areNeterminal = true;
			}
		}
		if (areNeterminal == false)
		{
			std::cout << "gramatica invalida : exista productie care nu are nici macar un neterminal in stanga \n";
			return false;
		}
	}

	for (auto& productie : m_P)
	{
		for (char c : productie.first)
		{
			if (m_VN.find(c) == m_VN.end()  && m_VT.find(c) == m_VT.end())
			{
				std::cout << "gramatica invalida : productiile contin caractere care nu sunt in VN sau VT \n";
				return false;
			}
		}
		for (char c : productie.second)
		{
			if (m_VN.find(c) == m_VN.end() && m_VT.find(c) == m_VT.end())
			{
				std::cout << "gramatica invalida: productiile contin caractere care nu sunt in VN sau VT \n";
				return false;
			}
		}

	}
	
	bool exista_producie_cu_S = false;
	for (const auto& prod : m_P) 
	{
		if (prod.first[0]==m_S && prod.first.size()== 1) 
		{
			exista_producie_cu_S = true;
		}
	}
	if(exista_producie_cu_S==false)
		std::cout << "gramatica invalida : nu exista productie in care doar m_S este in stanga \n";
	else 
		std::cout << "gramatica valida : \n";

	return exista_producie_cu_S;
}

bool Gramatica::isRegular(const Gramatica& gramatica)
{
	for (const auto& productie : gramatica.m_P)
	{
		for (auto it = productie.first.begin(); it != productie.first.end(); it++)
		{
			int numberLetters = 0;
			if (*it != NULL)
			{
				numberLetters++;
			}
			if (std::islower(*it))
			{
				return false;
			}
			if (numberLetters > 1)
			{
				return false;
			}
			//daca in partea stanga exista mai mult de un singur caracter, atunci returneaza fals. Daca acel caracter este mic, adica din multumea terminalelor, returneaza fals again.
		}

		for (auto it = productie.second.begin(); it != productie.second.end(); it++)
		{
			int numberLetters = 0;
			bool smallLetter = false, bigLetter = false;
			if (*it != NULL)
			{
				numberLetters++;
			}
			if (numberLetters > 2)
			{
				return false; //daca sunt mai mult de 2 caractere returnam false
			}
			if (std::islower(*it))
			{
				smallLetter = true;
			}
			else if (std::isupper(*it))
			{
				bigLetter = true;
			}
			if (bigLetter == true && smallLetter == false) //daca sunt doar caractere mari, returneaza false
			{
				return false;
			}
		}
	}

	return true;
}
