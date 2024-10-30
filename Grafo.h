#ifndef __GRAFO__H__
#define __GRAFO__H__
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <unordered_map>

template <class T>
class Grafo {
public:
    typedef std::vector<T> TVert;
    typedef std::vector<std::vector<bool>> TMatr;
    typedef std::vector<bool> TMark;

    TMatr m_costos;
    TVert l_vertices;

    Grafo();
    ~Grafo();
    unsigned long InsertarVertice(T v);
    void InsertarArista(unsigned long i, unsigned long j, bool costo);
    unsigned long ObtenerNumVertices();
    unsigned long ObtenerNumAristas();
    T ObtenerVertice(unsigned long i);
    bool ObtenerCostoArista(unsigned long i, unsigned long j);
    bool BuscarVertice(T v);
    bool BuscarArista(unsigned long i, unsigned long j);
    bool EliminarVertice(T v);
    bool EliminarArista(unsigned long i, unsigned long j);
    void imprimir();
    std::vector<T> ObtenerVertices() const;
};

#include "Grafo.hxx"

#endif
