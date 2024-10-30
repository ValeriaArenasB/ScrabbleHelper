#ifndef __DICCIONARIO__H
#define __DICCIONARIO__H
#include <list>
#include <string>
#include <iostream>
#include "palabra.h"

using namespace std;

class Diccionario {
public:
  Diccionario(string nombre, bool direccion);
  Diccionario();
  string ObtenerNombre() const;
  list <Palabra> obtenerLista() const;
  bool ObtenerDireccion() const;
  void FijarNombre(string nombre);
  void FijarLista(list<Palabra> lista);
  void FijarDireccion(bool direccion);
  void AgregarPalabra(Palabra npalabra);
  void EliminarPalabra(Palabra palabra);

protected:
  std::string nombre;
  list<Palabra> palabras;
  bool direccion;
};

#endif //__DICCIONARIO__H