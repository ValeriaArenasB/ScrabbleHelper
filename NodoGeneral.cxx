#include "NodoGeneral.h"

NodoGeneral::NodoGeneral(char dato) : dato(dato) {
    this->dato=dato;
    desc.clear();
}

NodoGeneral::~NodoGeneral() {
  typename std::list< NodoGeneral* >::iterator it;
  for (it = this->obtenerDesc().begin(); it != this->obtenerDesc().end(); it++)
    delete *it;
  this->desc.clear();
}

char& NodoGeneral::obtenerDato() {
  return this->dato;
}

std::list< NodoGeneral* > NodoGeneral::obtenerDesc(){
  return this->desc;
}

void NodoGeneral::fijarDato(char& val) {
  this->dato = val;
}

void NodoGeneral::limpiarLista() {
  this->desc.clear();
}

void NodoGeneral::adicionarDesc(NodoGeneral* n) {
  for (auto hijo : this->desc){
    if (hijo->obtenerDato() ==n->obtenerDato()) return;  // Evita insertar duplicados
  }
  //NodoGeneral *nuevoNodo = new NodoGeneral(n);
  this->desc.push_back(n);
}


bool NodoGeneral::eliminarDesc(char& val) {
  // buscar el nodo con el valor dado
  typename std::list< NodoGeneral* >::iterator it;
  NodoGeneral *aux;
  bool eliminado = false;

  for (it = this->desc.begin(); it != this->desc.end(); it++) {
    aux = *it;
    if (aux->obtenerDato() == val)
      break;
  }
  // si lo encontramos, eliminarlo
  if (it != this->desc.end()) {
    delete *it;
    this->desc.erase(it);
    eliminado = true;
  }

  return eliminado;
}

bool NodoGeneral::esHoja() {
  return this->desc.size() == 0;
}

int NodoGeneral::altura() {
  int alt = -1;

  if (this->esHoja()) {
    alt = 0;
  } else {
    int alth;
    typename std::list< NodoGeneral* >::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); it++) {
      alth = (*it)->altura();
      if (alt < alth+1)
        alt = alth+1;
    }
  }
  return alt;
}

void NodoGeneral::preOrden() {
  std::cout << this->dato << " ";
  typename std::list< NodoGeneral* >::iterator it;
  for (it = this->desc.begin(); it != this->desc.end(); it++) {
    (*it)->preOrden();
  }
}

// Buscar un hijo específico
NodoGeneral* NodoGeneral::buscarHijo(char ch) {
  for (auto hijo : desc) {
    if (hijo->dato == ch) {
      return hijo;
    } 
  }
  return nullptr;
}

