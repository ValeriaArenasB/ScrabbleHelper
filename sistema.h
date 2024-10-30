#ifndef SISTEMA_H
#define SISTEMA_H

#include "diccionario.h"
#include "ArbolGeneral.h"
#include "Grafo.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <limits>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <vector>

class Sistema {
protected:
    std::vector<Diccionario> diccionarios;
    std::vector<ArbolGeneral*> arboles;
    std::vector<ArbolGeneral*> arbolesInv;
    Grafo<std::string> grafo;

public:
    Sistema();
    std::vector<Diccionario> ObtenerDiccionarios() const;
    void FijarDiccionarios(const std::vector<Diccionario>& diccionarios);
    void AgregarDiccionario(const Diccionario& diccionario);
    void Inicializar(std::string& archivo);
    void IniciarInverso(std::string& archivo);
    void AbrirArchivo(std::string& archivo, bool modo);
    Palabra StringAPalabra(const std::string& str);
    int CalcularPuntaje(const std::string& palabra);
    int PuntajeLetra2_0(const char& letra);
    void Puntaje(const std::string& palabra);

    void FijarArboles(const std::vector<ArbolGeneral*>& nuevosArboles);
    void iniciarArbol(std::string& archivo);
    void iniciarArbolInverso(std::string& archivo);
    bool crearArbol(const Diccionario& dic);

    void AgregarArbol(ArbolGeneral* arbol);
    void palabrasPorPrefijo(std::string palabra);
    void palabrasPorSufijo(std::string palabra);
    std::vector<ArbolGeneral*> ObtenerArboles();
    std::vector<ArbolGeneral*> ObtenerArbolesInv();

    bool procesarArchivo(const std::string& archivo, bool direccion);
    bool buscarNodoPorPrefijo(ArbolGeneral* arbol, const std::string& prefijo, NodoGeneral*& nodoEncontrado);
    void recolectarPalabrasDesde(NodoGeneral* nodo, const std::string& prefijo, std::list<std::string>& palabras);

    int CalcularPuntajeArbol(const std::string& palabra, bool modo);

    void grafoDePalabras();
    bool difierenEnUnaLetra(const std::string& palabra1, const std::string& palabra2);

    void posiblesPalabras(const std::string& letras);
    bool letrasValidas(const std::string& letras) const;
    bool palabraValida(const std::string& palabra, std::string letrasModificadas, int comodines) const;
};

#endif // SISTEMA_H
