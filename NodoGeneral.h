#ifndef __NODOGENERAL_H__
#define __NODOGENERAL_H__

#include <list>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

class NodoGeneral {
  protected:
    char dato;
    std::list< NodoGeneral* > desc;
  public:
    NodoGeneral();
    NodoGeneral(char val);
   ~NodoGeneral();
    char& obtenerDato();
    std::list< NodoGeneral* > obtenerDesc();
    void fijarDato(char& val);
    void limpiarLista();
    bool eliminarDesc(char& val);
    bool esHoja();
    int altura();
    void preOrden();
    void adicionarDesc(NodoGeneral* n);
    NodoGeneral* buscarHijo(char ch);
};

#endif