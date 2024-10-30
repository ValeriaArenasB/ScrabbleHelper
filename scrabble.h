#ifndef __SCRABBLE_FUNCTIONS__H__
#define __SCRABBLE_FUNCTIONS__H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm> 
#include <list>
#include <vector>

using namespace std;

void salir();

// Búsqueda de palabras
void iniciarArbol(string &archivo);
void iniciarArbolInverso(string &archivo);
void palabrasPorPrefijo(string palabra);
void palabrasPorSufijo(string palabra);

// Combinaciones de letras
void grafoDePalabras();
void posiblesPalabras(string letras);

void abrirArchivo(string &archivo);
void ayuda();
void ayudaConParametro(string comando);

#endif