#include "diccionario.h"

Diccionario::Diccionario(string nombre, bool direccion): nombre(nombre), direccion(direccion){}

Diccionario::Diccionario(){}

string Diccionario::ObtenerNombre()const{
  return nombre;
}
list<Palabra> Diccionario::obtenerLista() const {
  return palabras;
}
bool Diccionario::ObtenerDireccion()const{
  return direccion;
}
void Diccionario::FijarNombre(string nombre){
  this->nombre = nombre;
}
void Diccionario::FijarLista(list<Palabra> lista){
  this->palabras = lista;
}
void Diccionario::FijarDireccion(bool direccion){
  this->direccion = direccion;
}
void Diccionario::AgregarPalabra(Palabra npalabra){
  palabras.push_back(npalabra);
}
void Diccionario::EliminarPalabra(Palabra palabra){
  palabras.remove(palabra);
}