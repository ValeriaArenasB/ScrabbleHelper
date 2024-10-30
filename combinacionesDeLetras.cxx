#include "sistema.h"
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>
#include <iostream>

bool Sistema::letrasValidas(const std::string& letras) const {
int contador = 0;
for (size_t i = 0; i < letras.size(); ++i) {
    char c = letras[i];
    if (!isalpha(c)) {
        if (c == '?') {
            contador++;
            if (contador > 1) {
                return false;
            }
        } else {
            return false;
        }
    }
}
return true;
}


bool Sistema::palabraValida(const std::string& palabra, std::string letrasModificadas, int comodines) const {
  int comodines_usados = 0;
  for (char c : palabra) {
      auto it = std::find(letrasModificadas.begin(), letrasModificadas.end(), c);
      if (it != letrasModificadas.end()) {
          letrasModificadas.erase(it);
      } else if (comodines_usados < comodines) {
          comodines_usados++;
      } else {
          return false; 
      }
  }
  return true;  
}

void Sistema::grafoDePalabras() {
  Grafo<std::string> grafo;
  std::vector<std::string> palabras;

  for (const Diccionario &dic : diccionarios) {
      for (const Palabra &palabra : dic.obtenerLista()) {
          std::string strPalabra = palabra.Obtenerletras();
          palabras.push_back(strPalabra);
          grafo.InsertarVertice(strPalabra);
      }
  }

  std::unordered_map<std::string, std::vector<int>> palabra_map;

  for (size_t index = 0; index < palabras.size(); ++index) {
      std::string str = palabras[index];
      for (size_t i = 0; i < str.size(); ++i) {
          char original = str[i];
          str[i] = '*';
          palabra_map[str].push_back(index);
          str[i] = original;
      }
  }

  for (const auto &pair : palabra_map) {
      const std::vector<int> &group = pair.second;
      for (size_t i = 0; i < group.size(); ++i) {
          for (size_t j = i + 1; j < group.size(); ++j) {
              if (difierenEnUnaLetra(palabras[group[i]], palabras[group[j]])) {
                  grafo.InsertarArista(group[i], group[j], true);
              }
          }
      }
  }

  this->grafo = grafo;
  std::cout << "Grafo construido correctamente." << std::endl;
}

bool Sistema::difierenEnUnaLetra(const std::string &palabra1, const std::string &palabra2) {
  if (palabra1.length() != palabra2.length()) {
      return false;
  }

  int diffCount = 0;
  for (size_t i = 0; i < palabra1.size(); i++) {
      if (palabra1[i] != palabra2[i]) {
          diffCount++;
          if (diffCount > 1) {
              return false;
          }
      }
  }
  return diffCount == 1;
}

void Sistema::posiblesPalabras(const std::string &letras) {
  if (!letrasValidas(letras)) {
      std::cout << "La cadena letras contiene símbolos inválidos." << std::endl;
      return;
  }

  std::set<std::string> palabrasValidas;
  std::vector<std::string> verticesGrafo = grafo.ObtenerVertices();
  std::queue<int> palabrasGrafo;

  for (size_t i = 0; i < verticesGrafo.size(); ++i) {
      palabrasGrafo.push(i);
  }

  std::string letrasMayus;
  letrasMayus.resize(letras.size());
  std::transform(letras.begin(), letras.end(), letrasMayus.begin(), ::toupper);

  if (letrasMayus.find('?') != std::string::npos) {
      std::string letrasModificadas = letrasMayus;
      letrasModificadas.erase(std::remove(letrasModificadas.begin(), letrasModificadas.end(), '?'), letrasModificadas.end());

      while (!palabrasGrafo.empty()) {
          int palabraIdx = palabrasGrafo.front();
          palabrasGrafo.pop();
          if (palabraValida(verticesGrafo[palabraIdx], letrasModificadas, 1)) {
              palabrasValidas.insert(verticesGrafo[palabraIdx]);
          }
      }
  } else {
      while (!palabrasGrafo.empty()) {
          int palabraIdx = palabrasGrafo.front();
          palabrasGrafo.pop();
          if (palabraValida(verticesGrafo[palabraIdx], letrasMayus, 0)) {
              palabrasValidas.insert(verticesGrafo[palabraIdx]);
          }
      }
  }

  if (!palabrasValidas.empty()) {
      std::cout << "Las posibles palabras a construir con las letras " << letras << " son:" << std::endl;
      for (const auto &palabra : palabrasValidas) {
          int puntaje = CalcularPuntaje(palabra);
          std::cout << "Palabra: " << palabra << ", Longitud: " << palabra.size() << ", Puntuación: " << puntaje << std::endl;
      }
  } else {
      std::cout << "No se encontraron palabras válidas para las letras proporcionadas." << std::endl;
  }
}
