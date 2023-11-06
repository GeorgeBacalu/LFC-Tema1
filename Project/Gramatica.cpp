#include "Gramatica.h"

Gramatica::Gramatica() : m_VN{ {} }, m_VT{ {} }, m_P{ {} }, m_S{ 'S' } {}

Gramatica::Gramatica(const std::set<char>& VN, const std::set<char>& VT, const std::set<Productie>& P, char S) : m_VN{ VN }, m_VT{ VT }, m_P{ P }, m_S{ S } {}

Gramatica::~Gramatica() {}

std::istream& operator>>(std::istream& in, Gramatica& gramatica) {
	int nrNeterminale, nrTerminale, nrProductii;
	in >> nrNeterminale;
	for (int i = 0; i < nrNeterminale; i++) {
		char neterminal;
		in >> neterminal;
		gramatica.m_VN.insert(neterminal);
	}
	in >> nrTerminale;
	for (int i = 0; i < nrTerminale; i++) {
		char terminal;
		in >> terminal;
		gramatica.m_VT.insert(terminal);
	}
	in >> gramatica.m_S >> nrProductii;
	std::string stanga, dreapta;
	for (int i = 0; i < nrProductii; i++) {
		in >> stanga >> dreapta;
		gramatica.m_P.emplace(stanga, dreapta);
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const Gramatica& gramatica) {
	out << "G = ({";
	for (char ch : gramatica.m_VN)
		out << ch << " ";
	out << "}, {";
	for (char ch : gramatica.m_VT)
		out << ch << " ";
	out << "}, " << gramatica.m_S << ", P}\n";
	for (const auto& productie : gramatica.m_P)
		if (!productie.first.empty())
			out << productie.first << "->" << productie.second << "\n";
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

void Gramatica::generare(int nrCuvinte) {
	m_cuvinteGenerate.clear(); // Goleste set ul de cuvinte generate
	std::string cuvantGenerat;


	std::random_device rd;
	std::mt19937 eng(rd());
	

	while (nrCuvinte > 0) {
	    cuvantGenerat = std::string(1, m_S); // Pornim de la simbolul de start

		while (true) {
			std::set<std::pair<std::string, std::string>> productiiAplicabile;

			for (const Productie& prod : m_P) {
				if (cuvantGenerat.find(prod.first) != std::string::npos) {
					productiiAplicabile.insert(prod);
				}
			}

			if (productiiAplicabile.empty()) {
				m_cuvinteGenerate.insert(cuvantGenerat);
				break;
			}
            
			std::uniform_int_distribution<int> distr(0, productiiAplicabile.size() - 1);
			int indexProductie = distr(eng);



			// Find the selected production using iterators
			auto it = productiiAplicabile.begin();
			std::advance(it, indexProductie);
			const Productie& selectedProd = *it;

			
			int pozitieInlocuire = cuvantGenerat.find(selectedProd.first);
			
			cuvantGenerat.replace(pozitieInlocuire, selectedProd.first.length(), selectedProd.second);
		}

		nrCuvinte--;
	}

	// Afiseaza cuvintele generate
	for (const std::string& cuvant : m_cuvinteGenerate) {
		std::cout << cuvant << std::endl;
	}
}
