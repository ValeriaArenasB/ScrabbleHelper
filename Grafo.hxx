#include "Grafo.h"

template <class T>
Grafo<T>::Grafo() {}

template <class T>
Grafo<T>::~Grafo() {}

template <class T>
unsigned long Grafo<T>::InsertarVertice(T v) {
    if (BuscarVertice(v)) {
        return std::distance(this->l_vertices.begin(), std::find(this->l_vertices.begin(), this->l_vertices.end(), v));
    }

    this->l_vertices.push_back(v);
    unsigned long indice = this->l_vertices.size() - 1;

    m_costos.resize(this->l_vertices.size());
    for (auto &fila : m_costos) {
        fila.resize(this->l_vertices.size(), false);
    }

    return indice;
}

template <class T>
void Grafo<T>::InsertarArista(unsigned long i, unsigned long j, bool costo) {
    if (i < this->l_vertices.size() && j < this->l_vertices.size()) {
        m_costos[i][j] = costo;
        m_costos[j][i] = costo; // Asumiendo grafo no dirigido
    }
}

template <class T>
unsigned long Grafo<T>::ObtenerNumVertices() {
    return this->l_vertices.size();
}

template <class T>
unsigned long Grafo<T>::ObtenerNumAristas() {
    unsigned long count = 0;
    for (const auto &row : this->m_costos) {
        count += std::count(row.begin(), row.end(), true);
    }
    return count / 2; // Contar cada arista una vez
}

template <class T>
T Grafo<T>::ObtenerVertice(unsigned long i) {
    return this->l_vertices[i];
}

template <class T>
bool Grafo<T>::ObtenerCostoArista(unsigned long i, unsigned long j) {
    return this->m_costos[i][j];
}

template <class T>
bool Grafo<T>::BuscarVertice(T v) {
    return std::find(this->l_vertices.begin(), this->l_vertices.end(), v) != this->l_vertices.end();
}

template <class T>
bool Grafo<T>::BuscarArista(unsigned long i, unsigned long j) {
    if (i < this->l_vertices.size() && j < this->l_vertices.size()) {
        return m_costos[i][j];
    }
    return false;
}

template <class T>
bool Grafo<T>::EliminarVertice(T v) {
    auto vertIt = std::find(this->l_vertices.begin(), this->l_vertices.end(), v);

    if (vertIt == this->l_vertices.end()) {
        return false;
    }

    unsigned long idx = std::distance(this->l_vertices.begin(), vertIt);
    this->l_vertices.erase(vertIt);

    m_costos.erase(m_costos.begin() + idx);
    for (auto &fila : m_costos) {
        fila.erase(fila.begin() + idx);
    }

    return true;
}

template <class T>
bool Grafo<T>::EliminarArista(unsigned long i, unsigned long j) {
    if (i < this->l_vertices.size() && j < this->l_vertices.size()) {
        m_costos[i][j] = false;
        m_costos[j][i] = false;
        return true;
    }
    return false;
}

template <class T>
void Grafo<T>::imprimir() {
    for (unsigned long i = 0; i < this->l_vertices.size(); i++) {
        for (unsigned long j = 0; j < this->l_vertices.size(); j++) {
            std::cout << (this->m_costos[i][j] ? "1" : "0") << "\t";
        }
        std::cout << std::endl;
    }
}

template <class T>
std::vector<T> Grafo<T>::ObtenerVertices() const {
    return l_vertices;
}
