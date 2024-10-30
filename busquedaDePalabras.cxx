#include "scrabble.h"
#include "sistema.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <iomanip>

bool Sistema::procesarArchivo(const string& archivo, bool direccion) {
  for (const auto& arbol : arboles) {
    if (arbol->obtenerNombre() == archivo && arbol->obtenerDireccion() == direccion) {
      return true;
    }
  }
  for (const auto& dicc : diccionarios) {
    if (dicc.ObtenerNombre() == archivo && dicc.ObtenerDireccion() == direccion) {
      return true;
    }
  }
  
  return false;
}

void Sistema::iniciarArbol(string &archivo) {
  bool arbolEncontrado = false;
  for (const ArbolGeneral* arbol : arboles) {
    if (arbol->obtenerNombre() == archivo && !arbol->obtenerDireccion()) {
      arbolEncontrado = true;
      cout << "El árbol del diccionario ya ha sido inicializado." << endl;
      break;
    }
  }

  if (!arbolEncontrado) {
    std::fstream file(archivo, std::ios::in);
    if (!file.is_open()) {
      cout << "El archivo " << archivo << " no existe o no puede ser leído." << endl;
      return;
    }

    ArbolGeneral* arbol = new ArbolGeneral(archivo, false);
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
        if (!arbol->insertarPalabra(palabraMayusculas)) {
          cout << "Error al insertar la palabra: " << palabraMayusculas << endl;
        }
      }
    }

    arboles.push_back(arbol);
    cout << "El árbol del diccionario se ha inicializado correctamente." << endl;
    file.close();
  }
}

void Sistema::iniciarArbolInverso(std::string &archivo) {
  bool arbolInversoEncontrado = false;
  for (const ArbolGeneral* arbol : arbolesInv) {
      if (arbol->obtenerNombre() == archivo && arbol->obtenerDireccion()) {
          arbolInversoEncontrado = true;
          std::cout << "El árbol del diccionario inverso ya ha sido inicializado." << std::endl;
          break;
      }
  }

  if (!arbolInversoEncontrado) {
      std::fstream file(archivo, std::ios::in);
      if (!file.is_open()) {
        std::cout << "El archivo " << archivo << " no existe o no puede ser leído." << std::endl;
        return;
      }

      ArbolGeneral* arbol = new ArbolGeneral(archivo, true);
      std::string palabra;
      while (file >> palabra) {
        bool esValida = true;
        std::string palabraMayusculas;
        for (char &c : palabra) {
          if (!isalpha(c)) {
            esValida = false;
            break;
          }
          palabraMayusculas += toupper(c);
        }

        if (esValida) {
          std::reverse(palabraMayusculas.begin(), palabraMayusculas.end());
          if (!arbol->insertarPalabra(palabraMayusculas)) {
            std::cout << "Error al insertar la palabra: " << palabraMayusculas << std::endl;
          }
        }
      }
    arbolesInv.push_back(arbol);
    std::cout << "El árbol del diccionario inverso se ha inicializado correctamente." << std::endl;
    file.close();
  }
}



bool Sistema::crearArbol(const Diccionario& dic) {
  ArbolGeneral* arbol = new ArbolGeneral(dic.ObtenerNombre(), dic.ObtenerDireccion());
  bool resultado = true;

  for (const Palabra& palabra : dic.obtenerLista()) {
    std::string palabraModificada = palabra.Obtenerletras();
    if (!arbol->insertarPalabra(palabraModificada)) {
      std::cout << "Error al insertar la palabra: " << palabraModificada << std::endl;
      resultado = false;
      break;
    }
  }
  
  if (resultado) {
      if (dic.ObtenerDireccion()) {
          arbolesInv.push_back(arbol);  // Añade a árboles invertidos
      } else {
          arboles.push_back(arbol);     // Añade a árboles normales
      }
  } else {
    std::cout << "Error al crear el árbol." << std::endl;
    delete arbol;
  }
  return resultado;
}

bool Sistema::buscarNodoPorPrefijo(ArbolGeneral* arbol, const std::string& prefijo, NodoGeneral*& nodoEncontrado) {
  NodoGeneral* actual = arbol->obtenerRaiz();
  for (char ch : prefijo) {
    NodoGeneral* hijo = actual->buscarHijo(ch);
    if (!hijo) return false;
    actual = hijo;
  }
  nodoEncontrado = actual;
  return true;
}

void Sistema::palabrasPorPrefijo(std::string prefijo) {
  std::string pf;
  std::transform(prefijo.begin(), prefijo.end(), std::back_inserter(pf), ::toupper);
  std::list<std::string> palabras;
  bool prefijoEncontrado = false;

  for (ArbolGeneral* arbol : this->arboles) {
    NodoGeneral* nodoEncontrado;
    if (buscarNodoPorPrefijo(arbol, pf, nodoEncontrado)) {
      recolectarPalabrasDesde(nodoEncontrado, pf, palabras);
      prefijoEncontrado = true;
    }
  }

  if (!prefijoEncontrado) {
    std::cout << "El prefijo " << prefijo << " no pudo encontrarse en el diccionario." << std::endl;
  } else {
    std::cout << "Las palabras que inician con este prefijo son: " << std::endl;
    int anchoMaximo = 0;
    for (const std::string& palabra : palabras) {
      if (palabra.length() > anchoMaximo) {
        anchoMaximo = palabra.length();
      }
    }
    for (const std::string& palabra : palabras) {
      int puntaje = CalcularPuntajeArbol(palabra, 0);
      std::cout << std::left << std::setw(anchoMaximo + 2) << palabra
                << "Longitud " << std::right << std::setw(2) << palabra.length() << ", "
                << "Puntaje " << puntaje << std::endl;
    }
  }
}

void Sistema::recolectarPalabrasDesde(NodoGeneral* nodo, const std::string& prefijoActual, std::list<std::string>& palabras) {
    if (!nodo) return;
    if (nodo->esHoja() && nodo->obtenerDato() != '0') {
        palabras.push_back(prefijoActual);
    }
    for (auto hijo : nodo->obtenerDesc()) {
        if (nodo->obtenerDato() != '0' || hijo->obtenerDato() != '0') {
            recolectarPalabrasDesde(hijo, prefijoActual + hijo->obtenerDato(), palabras);
        } else {
            recolectarPalabrasDesde(hijo, prefijoActual, palabras);
        }
    }
}

void Sistema::palabrasPorSufijo(std::string sufijo) {
    std::string sufijoMayusculas;
    std::transform(sufijo.begin(), sufijo.end(), std::back_inserter(sufijoMayusculas), ::toupper);
    std::reverse(sufijoMayusculas.begin(), sufijoMayusculas.end());
    std::list<std::string> palabras;
    bool sufijoEncontrado = false;

    for (ArbolGeneral* arbol : arbolesInv) {
        NodoGeneral* nodoEncontrado;
        if (buscarNodoPorPrefijo(arbol, sufijoMayusculas, nodoEncontrado)) {
            recolectarPalabrasDesde(nodoEncontrado, sufijoMayusculas, palabras);
            sufijoEncontrado = true;
        }
    }

    if (!sufijoEncontrado) {
        std::cout << "El sufijo " << sufijo << " no pudo encontrarse en el diccionario." << std::endl;
    } else {
        std::cout << "Las palabras que terminan con este sufijo son: " << std::endl;
        int anchoMaximo = 0;
        for (const std::string& palabra : palabras) {
            if (palabra.length() > anchoMaximo) {
                anchoMaximo = palabra.length();
            }
        }
        for (const std::string& palabra : palabras) {
            std::string palabraInvertida = palabra;
            std::reverse(palabraInvertida.begin(), palabraInvertida.end());
            int puntaje = CalcularPuntajeArbol(palabraInvertida, 1); // Modo 1 para árboles invertidos
            if (puntaje != -1) {
                std::cout << std::left << std::setw(anchoMaximo + 2) << palabraInvertida
                          << "Longitud " << std::right << std::setw(2) << palabraInvertida.length() << ", "
                          << "Puntaje " << puntaje << std::endl;
            } else {
                std::cout << "La palabra " << palabraInvertida << " no se encuentra en los diccionarios." << std::endl;
            }
        }
    }
}
