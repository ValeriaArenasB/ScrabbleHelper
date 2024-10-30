#include "sistema.h"
#include "scrabble.h"

int contarPalabras(const string &input) ;
void comandos(string linea, Sistema &s);

using namespace std;

 int main() {
  string entrada;
  Sistema scrabble = Sistema(); 
   
  cout << "Bienvenido al sistema de apoyo de Scrabble, lo apoyaremos en la construcción de la mejor palabra! \nDigite su comando, en caso de no saber los comandos digite 'ayuda' \n";

  while (entrada != "salir") {
    cout << "\n$ ";
    getline(cin, entrada);
    comandos(entrada, scrabble); 
  };
  return 0;
}
