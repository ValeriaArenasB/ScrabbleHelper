#include "ArbolGeneral.h"
#include <queue>

ArbolGeneral::ArbolGeneral() {
  this->raiz = nullptr;
  this->direccion = false; // Suposición de un valor por defecto
}

// Constructor con parámetros
ArbolGeneral::ArbolGeneral(string nombre, bool direccion) : nombre(nombre), direccion(direccion) {
  this->raiz = new NodoGeneral('0');
}

// Destructor
ArbolGeneral::~ArbolGeneral() {
  delete this->raiz;
  this->raiz = nullptr;
}


bool ArbolGeneral::esVacio() {
 return this->raiz == NULL;
}

NodoGeneral* ArbolGeneral::obtenerRaiz() const{
 return this->raiz;
}

string ArbolGeneral::obtenerNombre() const{
 return this->nombre;
}

void ArbolGeneral::fijarNombre(string nombre) {
  this->nombre = nombre;
}

bool ArbolGeneral::obtenerDireccion() const{
 return this->direccion;
}

void ArbolGeneral::fijarRaiz(NodoGeneral* nraiz) {
   this->raiz = nraiz;
}

bool ArbolGeneral::existeHijo(NodoGeneral* padre, char n) {
  // Iterar sobre los hijos del nodo padre
  for (NodoGeneral* hijo : padre->obtenerDesc()) {
    // Si el valor del hijo es igual al valor que se quiere insertar, retorna verdadero
    if (hijo->obtenerDato() == n) {
      return true;
    }
  }
  // Si no se encontró un hijo con el mismo valor, retorna falso
  return false;
}

bool ArbolGeneral::insertarPalabra(const string& palabra) {
  if (!raiz) raiz = new NodoGeneral('0'); // Asegura que la raíz exista

  NodoGeneral* actual = raiz;
  for (char ch : palabra) {
    NodoGeneral* hijo = actual->buscarHijo(ch);
    if (!hijo) {
      hijo = new NodoGeneral(ch);
      actual->adicionarDesc(hijo);
  }
    actual = hijo;
  }
  return true; 
}

bool ArbolGeneral::insertarNodo(char padre, char n) {
  if (this->raiz == nullptr) {
    this->raiz = new NodoGeneral('0'); // Inicialización por defecto si es necesario
    if (padre == '0') {
      padre = this->raiz->obtenerDato(); // Si padre es '0', usamos la raíz
    } else {
      return false; // Si no hay raíz y el padre no es '0', retorno falso
    }
  }

  NodoGeneral* nodoPadre = buscarNodo(this->raiz, padre);
  if (nodoPadre != nullptr) {
    if (!existeHijo(nodoPadre, n)) {
      nodoPadre->adicionarDesc(new NodoGeneral(n));
      return true;
    } else {
      return false; // Nodo ya existe
    }
  } else {
    return false; // No se encontró el nodo padre
  }
}

NodoGeneral* ArbolGeneral::buscarNodo(NodoGeneral* nodo, const char& valor) {
  if (nodo == nullptr) return nullptr;
  if (nodo->obtenerDato() == valor) return nodo;

  for (NodoGeneral* hijo : nodo->obtenerDesc()) {
      NodoGeneral* resultado = buscarNodo(hijo, valor);
      if (resultado != nullptr) return resultado;
  }
  return nullptr;
}

bool ArbolGeneral::eliminarNodo(char valor) {
  // Caso especial: si la raíz es el nodo a eliminar
  if (this->raiz != nullptr && this->raiz->obtenerDato() == valor) {
     // Elimina toda la subestructura del árbol
     this->raiz->limpiarLista();
     delete this->raiz;
     this->raiz = nullptr;
     return true;
   }
   // Iniciar la búsqueda y eliminación recursiva desde la raíz
   return eliminarNodoRecursivo(nullptr, this->raiz, valor);
}

bool ArbolGeneral::eliminarNodoRecursivo(NodoGeneral* padre, NodoGeneral* nodoActual, char valor){
 if (nodoActual == nullptr) return false;
 if (nodoActual->obtenerDato() == valor){
   //no tiene padre porque tiene raíz
   if (padre == nullptr){
     delete this->raiz;
     this->raiz = nullptr;
   }
   else{
     padre->obtenerDesc().remove(nodoActual);
   }
   return true;

 }
 //eliminar todos los hijos del nodo actual
 typename std::list<NodoGeneral*>::iterator it;
 for (it = nodoActual->obtenerDesc().begin(); it != nodoActual->obtenerDesc().end(); ++it){
   if (eliminarNodoRecursivo(nodoActual, *it, valor)){
     return true;
   }
 }
 return false;
}

int ArbolGeneral::altura() {
 if (this->esVacio() && this->raiz == nullptr) {
   return -1;
 } else {
   return (this->raiz)->altura();
 }
}

unsigned int ArbolGeneral::tamano() {
 return tamanoAux(this->raiz);
}

unsigned int ArbolGeneral::tamanoAux(NodoGeneral* nodo) {
 if (nodo == nullptr) {
   return 0; // Si el nodo es nullptr, no contribuye al tamaño del árbol.
 }
 // Inicia el contador de tamaño para este nodo.
 unsigned int tam = 1; // Contando el nodo actual.

 // Itera sobre todos los hijos del nodo actual y suma sus tamaños.
 typename std::list<NodoGeneral*>::iterator it;
 for (it = nodo->obtenerDesc().begin(); it != nodo->obtenerDesc().end(); ++it) {
   tam += tamanoAux(*it); // Suma el tamaño del subárbol hijo.
 }
 return tam; // Retorna el tamaño total encontrado desde este nodo hacia abajo.
}

void ArbolGeneral::preOrden() {
  if (!this->esVacio())
     (this->raiz)->preOrden();
}

void ArbolGeneral::posOrden() {
 if(this->raiz != nullptr)
   this->posOrden(this->raiz);
}

void ArbolGeneral::posOrden(NodoGeneral* nodo) {
  if (nodo == nullptr) return; 
  typename std::list<NodoGeneral*>::iterator it;
  for (it = nodo->obtenerDesc().begin(); it != nodo->obtenerDesc().end(); ++it) {
    posOrden(*it);
  }
  std::cout << nodo->obtenerDato() << " ";
}

void ArbolGeneral::nivelOrden() {
 // NO ES RECURRENTE (O RECURSIVO)
 if(this->raiz == nullptr) return; //si está vac{io, no hay nada que hacer.
 std::queue<NodoGeneral*> cola;
 // ubicarme en la raiz
 // poner la raiz en una cola
 cola.push(this->raiz);

 // hacer un ciclo mientras haya algo en la cola
 while(!cola.empty()){
   // - saco el primero disponible en la cola
   NodoGeneral* nodo = cola.front();
   cola.pop();

   // - imprimo su dato
   std::cout << nodo->obtenerDato() << " ";
   // - inserto en la cola todos sus hijos
   typename std::list<NodoGeneral*>::iterator it;
   for (it = nodo->obtenerDesc().begin(); it != nodo->obtenerDesc().end(); ++it)
     cola.push(*it);
 }
}

