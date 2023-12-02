#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <map>



class AutomatFinit
{
private:
    std::set<std::string> stari;
    std::set<char> alfabet;
    std::string stareInitiala;
    std::set<std::string> stariFinale;
    std::map<std::pair<std::string, char>, std::vector<std::string>> functieTranzitie;
 
  public:

      AutomatFinit();
      AutomatFinit(std::set<std::string>& stari, std::set<char>& alfabet, std::string& stareInitiala, std::set<std::string>& stariFinale,std::map<std::pair<std::string, char>, std::vector<std::string>>& functieTranzitie);
      ~AutomatFinit();
      friend std::istream& operator>>(std::istream& in, AutomatFinit& automatFinit);
      friend std::ostream& operator<<(std::ostream& out, const AutomatFinit& automatFinit);
      const std::string& getStareInitiala() const;
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

