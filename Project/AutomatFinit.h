#pragma once

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>

using FunctieTranzitie = std::map<std::pair<std::string, char>, std::vector<std::string>>;

class AutomatFinit
{
private:
	std::set<std::string> stari;
	std::set<char> alfabet;
	std::string stareInitiala;
	std::set<std::string> stariFinale;
	FunctieTranzitie functieTranzitie;
public:
	AutomatFinit();
	AutomatFinit(const std::set<std::string>& stari, const std::set<char>& alfabet, const std::string& stareInitiala, const std::set<std::string>& stariFinale, const FunctieTranzitie& functieTranzitie);
	~AutomatFinit() = default;
	friend std::istream& operator>>(std::istream& in, AutomatFinit& automatFinit);
	friend std::ostream& operator<<(std::ostream& out, const AutomatFinit& automatFinit);

	std::set<std::string> getStari() const;
	const std::set<char>& getAlfabet() const;
	const std::string& getStareInitiala() const;
	std::set<std::string> getStariFinale() const;
	FunctieTranzitie getFunctieTranzitie() const;
	void setStari(const std::set<std::string>& stari);
	void setAlfabet(const std::set<char>& alfabet);
	void setStareInitiala(const std::string& stareInitiala);
	void setStariFinale(const std::set<std::string>& stariFinale);
	void setFunctieTranzitie(const FunctieTranzitie& functieTranzitie);

	bool verificareAutomat();
private:
	bool multimeStariNevida();
	bool alfabetNevid();	
	bool stareInitialaInMultimeaStari();
	bool stariFinaleInMultimeaStari();
	bool functieTranzitieCorecta();
public:
	bool esteDeterminist();
	bool verificareCuvant(const std::string& stareCurenta, const std::string& cuvant);
};