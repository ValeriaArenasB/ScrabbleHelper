#include "palabra.h"
#define MAX_LENGTH 100

Palabra::Palabra(std::string palabra) {
  letras.assign(palabra.begin(), palabra.end());
}

Palabra::Palabra() {
}

std::string Palabra::Obtenerletras() const {
  std::string temp;
  for(auto it = letras.begin(); it != letras.end(); ++it){
    temp += *it;
  }
  return temp;
}

bool operator==(const Palabra& lhs, const Palabra& rhs) {
  return lhs.Obtenerletras() == rhs.Obtenerletras();
}


void Palabra::Fijarletras(std::string palabra) {
  letras.clear();
  if (palabra.size() > MAX_LENGTH) {
    std::cerr << "Error: El tamaño de la palabra excede el máximo permitido\n";
    return;
    }
  
  letras.assign(palabra.begin(), palabra.end());
}
