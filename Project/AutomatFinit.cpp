#include "AutomatFinit.h"

AutomatFinit::AutomatFinit() : stari{ {} }, alfabet{ {} }, stareInitiala{ "" }, stariFinale{ {} }, functieTranzitie{ {} } {}

AutomatFinit::AutomatFinit(const std::set<std::string>& stari, const std::set<char>& alfabet, const std::string& stareInitiala, const std::set<std::string>& stariFinale, const FunctieTranzitie& functieTranzitie)
	: stari{ stari }, alfabet{ alfabet }, stareInitiala{ stareInitiala }, stariFinale{ stariFinale }, functieTranzitie{ functieTranzitie } {}

std::set<std::string> AutomatFinit::getStari() const
{
	return stari;
}

const std::set<char>& AutomatFinit::getAlfabet() const
{
	return alfabet;
}

const std::string& AutomatFinit::getStareInitiala() const
{
	return stareInitiala;
}

std::set<std::string> AutomatFinit::getStariFinale() const
{
	return stariFinale;
}

FunctieTranzitie AutomatFinit::getFunctieTranzitie() const
{
	return functieTranzitie;
}

void AutomatFinit::setStari(const std::set<std::string>& stari)
{
	this->stari = stari;
}

void AutomatFinit::setAlfabet(const std::set<char>& alfabet)
{
	this->alfabet = alfabet;
}

void AutomatFinit::setStareInitiala(const std::string& stareInitiala)
{
	this->stareInitiala = stareInitiala;
}

void AutomatFinit::setStariFinale(const std::set<std::string>& stariFinale)
{
	this->stariFinale = stariFinale;
}

void AutomatFinit::setFunctieTranzitie(const FunctieTranzitie& functieTranzitie)
{
	this->functieTranzitie = functieTranzitie;
}

bool AutomatFinit::verificareAutomat()
{
	if (multimeStariNevida() && alfabetNevid() && stareInitialaInMultimeaStari() && stariFinaleInMultimeaStari() && functieTranzitieCorecta())
	{
		std::cout << "Automat valid\n\n";
		return true;
	}
	return false;
}

bool AutomatFinit::multimeStariNevida()
{
	if (stari.size() == 0)
	{
		std::cout << "Automat nevalid : Multimea de stari este vida\n";
		return false;
	}
	return true;
}

bool AutomatFinit::alfabetNevid()
{
	if (alfabet.size() == 0)
	{
		std::cout << "Automat nevalid : Alfabetul este vid\n";
		return false;
	}
	return true;
}

bool AutomatFinit::stareInitialaInMultimeaStari()
{
	if (stareInitiala.size() == 0)
	{
		std::cout << "Automat nevalid : Starea initiala este vida\n";
		return false;
	}

	if (stari.find(stareInitiala) == stari.end())
	{
		std::cout << "Automat nevalid : Starea initiala nu se afla in multimea de stari\n";
		return false;
	}
	return true;
}

bool AutomatFinit::stariFinaleInMultimeaStari()
{
	if (stariFinale.size() == 0)
	{
		std::cout << "Automat nevalid : Multimea de stari finale este vida\n";
		return false;
	}

	for (const auto& stareFinala : stariFinale)
		if (stari.find(stareFinala) == stari.end())
		{
			std::cout << "Automat nevalid : Starea finala nu se afla in multimea de stari\n";
			return false;
		}
	return true;
}

bool AutomatFinit::functieTranzitieCorecta()
{
	if (functieTranzitie.size() == 0)
	{
		std::cout << "Automat nevalid : Functia de tranzitie este vida\n";
		return false;
	}

	for (const auto& tranzitie : functieTranzitie)
	{
		const auto& pereche = tranzitie.first;
		const auto& stariUrmatoare = tranzitie.second;
		if (stari.find(pereche.first) == stari.end())
		{
			std::cout << "Automat nevalid : Starea " << pereche.first << " din functia de tranzitie nu se afla in multimea de stari\n";
			return false;
		}
		if (alfabet.find(pereche.second) == alfabet.end())
		{
			std::cout << "Automat nevalid : Simbolul " << pereche.second << " din functia de tranzitie nu se afla in alfabet\n";
			return false;
		}
		for (const auto& stare : stariUrmatoare)
			if (stari.find(stare) == stari.end())
			{
				std::cout << "Automat nevalid : Starea " << stare << " din functia de tranzitie nu se afla in multimea de stari\n";
				return false;
			}
	}
	return true;
}

bool AutomatFinit::esteDeterminist()
{
	for (const auto& stare : stari)
		for (const auto& simbol : alfabet)
		{
			if (functieTranzitie.find({ stare,simbol }) == functieTranzitie.end())
			{
				std::cout << "Automatul nu este determinist: exista stare si simbol care nu au tranzitie\n\n";
				return false;
			}
			if (functieTranzitie[{stare, simbol}].size() > 1)
			{
				std::cout << "Automatul nu este determinist: exista stare si simbol care au mai multe tranzitii\n\n";
				return false;
			}
		}
	std::cout << "Automatul este determinist\n\n";
	return true;
}

bool AutomatFinit::verificareCuvant(const std::string& stareCurenta, const std::string& cuvant)
{
	if (cuvant.empty())
		return stariFinale.find(stareCurenta) != stariFinale.end();

	char simbol = cuvant[0];

	auto it = functieTranzitie.find({ stareCurenta, simbol });

	if (it != functieTranzitie.end())
	{
		const auto& stariUrmatoare = it->second;
		for (const auto& stareUrmatoare : stariUrmatoare)
			if (verificareCuvant(stareUrmatoare, cuvant.substr(1)))
				return true;
	}
	return false;
}

std::istream& operator>>(std::istream& in, AutomatFinit& automatFinit)
{
	int nrStari, nrElementeAlfabet, nrStariFinale, nrTranzitii;
	in >> nrStari;

	for (size_t i = 0; i < nrStari; i++) {
		std::string stare;
		in >> stare;
		automatFinit.stari.insert(stare);
	}

	in >> nrElementeAlfabet;
	for (size_t i = 0; i < nrElementeAlfabet; i++) {
		char simbol;
		in >> simbol;
		automatFinit.alfabet.insert(simbol);
	}

	in >> automatFinit.stareInitiala >> nrStariFinale;
	for (size_t i = 0; i < nrStariFinale; i++) {
		std::string stareFinala;
		in >> stareFinala;
		automatFinit.stariFinale.insert(stareFinala);
	}

	in >> nrTranzitii;
	for (size_t i = 0; i < nrTranzitii; i++) {
		std::string stare1, stare2;
		char simbol;
		in >> stare1 >> simbol >> stare2;
		automatFinit.functieTranzitie[{stare1, simbol}].push_back(stare2);
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, const AutomatFinit& automatFinit) {
	out << "AutomatFinit = ({ ";
	for (const auto& stare : automatFinit.stari)
		out << stare << " ";
	out << "}, { ";
	for (const auto& simbol : automatFinit.alfabet)
		out << simbol << " ";
	out << "}, funtieTranzitie, " << automatFinit.stareInitiala << ", { ";
	for (const auto& stareFinala : automatFinit.stariFinale)
		out << stareFinala << " ";
	out << "})\n\n";

	out << "functieTranzitie :\n";
	for (const auto& tranzitie : automatFinit.functieTranzitie) {
		const auto& pereche = tranzitie.first;
		const auto& stariUrmatoare = tranzitie.second;
		for (const auto& stareUrmatoare : stariUrmatoare)
			out << "  (" << pereche.first << " , " << pereche.second << ") -> " << stareUrmatoare << "\n";
	}
	out << "\n";

	return out;
}