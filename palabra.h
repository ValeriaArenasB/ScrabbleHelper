#ifndef __PALABRA__H
#define __PALABRA__H
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Palabra{
  public:
  Palabra();
  Palabra(string palabra);
  std::string Obtenerletras() const;
  void Fijarletras(std::string palabra);

  protected:
  vector <char> letras;
};

bool operator==(const Palabra& lhs, const Palabra& rhs);


#endif 