#ifndef __ARBOLGENERAL_H__
#define __ARBOLGENERAL_H__

#include "NodoGeneral.h"

class ArbolGeneral {
  protected:
    NodoGeneral* raiz;
    bool direccion; 
    string nombre;
  public:
    ArbolGeneral();
    ArbolGeneral(string nombre, bool direccion);
    ~ArbolGeneral();
    string obtenerNombre() const;
    void fijarNombre(string nombre);
    bool esVacio();
    NodoGeneral* obtenerRaiz() const;
    bool obtenerDireccion() const;
    void fijarRaiz(NodoGeneral* nraiz);
    bool insertarNodo(char padre, char n);
    void eliminarSubarbol(NodoGeneral* nodo);
    bool eliminarNodo(char n); 
    bool eliminarNodoRecursivo(NodoGeneral* padre, NodoGeneral* nodoActual, char n);
    int altura();
    unsigned int tamano();
    unsigned int tamanoAux(NodoGeneral* nodo);
    void preOrden();
    void posOrden();
    void posOrden(NodoGeneral* nodo);
    void nivelOrden();
    NodoGeneral* buscarNodo(NodoGeneral* nodo, const char& valor);
    void eliminarTodosLosDescendientes(NodoGeneral* nodo);
    bool existeHijo(NodoGeneral* padre, char n);  
    bool insertarPalabra(const string& palabra);

};

#endif