#include "sistema.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Sistema::Sistema(){}

std::vector<Diccionario> Sistema::ObtenerDiccionarios() const {
  return diccionarios;
}

std::vector<ArbolGeneral*> Sistema::ObtenerArboles() {
  return arboles;
}
std::vector<ArbolGeneral*> Sistema::ObtenerArbolesInv() {
  return arbolesInv;
}

void Sistema::FijarDiccionarios(const std::vector<Diccionario>& nuevosDiccionarios) {
  diccionarios = nuevosDiccionarios;
}

void Sistema::FijarArboles(const std::vector<ArbolGeneral*>& nuevosArboles) {
  arboles= nuevosArboles;
}

void Sistema::AgregarDiccionario(const Diccionario& diccionario) {
  diccionarios.push_back(diccionario);
}

void Sistema::AgregarArbol(ArbolGeneral* arbol) {
  arboles.push_back(arbol);
}

void Sistema::AbrirArchivo(std::string& archivo, bool modo) {
  static std::vector<std::string> archivosAbiertosNormal;
  static std::vector<std::string> archivosAbiertosInverso;
  bool encontrado = false;
  
  if(modo){
    std::vector<std::string>::iterator it;
    for (it = archivosAbiertosNormal.begin(); it != archivosAbiertosNormal.end(); ++it) {
      if (*it == archivo) {
        encontrado = true;
        std::cout << "El archivo " << archivo << " ya está abierto." << std::endl;
        return;
      }
    }
    if(!encontrado) archivosAbiertosNormal.push_back(archivo);
  }
  else {
  std::vector<std::string>::iterator it;
  for (it = archivosAbiertosInverso.begin(); it != archivosAbiertosInverso.end(); ++it) {
    if (*it == archivo) {
      encontrado = true;
      std::cout << "El archivo " << archivo << " ya está abierto." << std::endl;
      return;
    }
  }
    if(!encontrado) archivosAbiertosInverso.push_back(archivo);
  }
  std::fstream file(archivo, std::ios::in);
  if (!file.is_open()) {
    std::cerr << "El archivo " << archivo << " no pudo ser abierto." << std::endl;
    return;
  }
  std::cout << "El archivo " << archivo << " se abrió correctamente." << std::endl;
}

Palabra Sistema::StringAPalabra(const string& str) {
  Palabra p;
  p.Fijarletras(str);
  return p;
}


void Sistema::Inicializar(string &archivo) {
  AbrirArchivo(archivo, true);
  fstream file;
  file.open(archivo, ios::in);
  if (file.fail()) return;
  
  Diccionario* d = new Diccionario(archivo, false);
  string palabra;
    while (file >> palabra) {
      bool esValida = true;
      string palabraMayusculas; 

      for (char &c : palabra) {
        if (!isalpha(c)) {
          esValida = false;
          break;
        }
        palabraMayusculas += toupper(c); 
      }

    if (esValida) {
      Palabra p = StringAPalabra(palabraMayusculas);
      d->AgregarPalabra(p);
    }
  }
  diccionarios.push_back(*d);
  file.close();
  
}

void Sistema::IniciarInverso(string &archivo) {
  AbrirArchivo(archivo, false);
  fstream file(archivo, ios::in);
  if (file.fail()) {
    return;
  }

  Diccionario* d = new Diccionario(archivo, true);
  string palabra;

  while (file >> palabra) {
    bool esValida = true;
    string palabraMayusculas; 
    
    for (char &c : palabra) {
      if (!isalpha(c)) {
        esValida = false;
        break;
      }
      palabraMayusculas += toupper(c);
    }
    if (esValida) {
      reverse(palabraMayusculas.begin(), palabraMayusculas.end());
      Palabra p = StringAPalabra(palabraMayusculas);
      d->AgregarPalabra(p);
    }
  }
  diccionarios.push_back(*d);
  file.close();
}

int Sistema::CalcularPuntaje(const string& palabra) {
  string palabraMayusculas;
  string p= palabra;
  for(char& c : p)
    palabraMayusculas += toupper(c);
    int puntaje = 0;
    bool palabraEncontrada = false;

    for (const Diccionario& diccionario : diccionarios) {
      list<Palabra> palabras = diccionario.obtenerLista();

      for (const Palabra& palabraDiccionario : palabras) {
        string palabraActual = palabraDiccionario.Obtenerletras();
        if (palabraActual == palabraMayusculas) { 
          palabraEncontrada = true;
          for (char letra : palabraActual) {
            puntaje += PuntajeLetra2_0(letra);
          }
          break;
        }
      }
      if (palabraEncontrada) {
        break;
      }
    }
    if (!palabraEncontrada) {
      cout << "La palabra no se encuentra en los diccionarios." << endl;
      return -1;
    }
  return puntaje;
}

int Sistema::CalcularPuntajeArbol(const std::string& palabra, bool modo) {
  std::string palabraMayusculas;
  for (char c : palabra) {
      palabraMayusculas += toupper(c);
  }

  NodoGeneral* nodoActual = nullptr;
  const std::vector<ArbolGeneral*>& arbolesARecorrer = modo ? arbolesInv : arboles;
  if (modo) {
    std::reverse(palabraMayusculas.begin(), palabraMayusculas.end());
  }

  for (ArbolGeneral* arbol : arbolesARecorrer) {
    NodoGeneral* actual = arbol->obtenerRaiz();
    bool encontrado = true;
    for (char ch : palabraMayusculas) {
      NodoGeneral* hijo = actual->buscarHijo(ch);
      if (!hijo) {
        encontrado = false;
        break;
      }
      actual = hijo;
    }
    if (encontrado) {
      nodoActual = actual;
      break;
    }
  }

  if (nodoActual == nullptr) {
    return -1;
  }

  int puntaje = 0;
  for (char letra : palabraMayusculas) {
    puntaje += PuntajeLetra2_0(letra);
  }

  return puntaje;
}

int Sistema::PuntajeLetra2_0(const char& letra) {
  vector<vector<char>> letras = {
      {'A', 'E', 'I', 'O', 'U', 'L', 'N', 'R', 'T', 'S'},
      {'D', 'G'},
      {'B', 'C', 'M', 'P'},
      {'F', 'H', 'V', 'W', 'Y'},
      {'K'},
      {'J', 'X'},
      {'Q', 'Z'}
  };
  vector<int> puntajes = {1, 2, 3, 4, 5, 8, 10};
  char letraUpper = toupper(letra);

  for (size_t i = 0; i < letras.size(); ++i) {
    if (find(letras[i].begin(), letras[i].end(), letraUpper) != letras[i].end()) {
      return puntajes[i];
    }
  }
  return 0;
}

void Sistema::Puntaje(const string& palabra){
  int puntajePalabra = CalcularPuntaje(palabra);

  if(puntajePalabra != -1){
    cout<<"La palabra tiene un puntaje de "<<puntajePalabra<<endl;
  }
}


