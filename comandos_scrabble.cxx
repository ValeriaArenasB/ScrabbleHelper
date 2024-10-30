#include "sistema.h"
#include "scrabble.h"

int contarPalabras(string &input) {
  istringstream sstream(input);
  string palabra;
  int contador = 0;
  while (sstream >> palabra) {
    contador++;
  }
  return contador;
}

void comandos(string linea, Sistema& s){
  string comando, parametro;
  stringstream str(linea);
  getline(str, comando, ' ');
  getline(str, parametro);
  int cantidadPalabras = contarPalabras(linea);

  if (comando == "ayuda" && cantidadPalabras == 1) {
    ayuda();
    return;
  }
  if (comando == "ayuda" && cantidadPalabras ==2) {
    ayudaConParametro(parametro);
    return;
  }
  if (comando == "grafo_de_palabras" && cantidadPalabras == 1) {
  s.grafoDePalabras();
  return;
  }

  if (cantidadPalabras == 2) {
    if (comando == "inicializar") {
      s.Inicializar(parametro);
    } else if (comando == "iniciar_inverso") {
      s.IniciarInverso(parametro);
    } else if (comando == "puntaje") {     
      s.Puntaje(parametro);
    } else if (comando == "iniciar_arbol") {
      s.iniciarArbol(parametro);
    } else if (comando == "iniciar_arbol_inverso") {
      s.iniciarArbolInverso(parametro);
    } else if (comando == "palabras_por_prefijo") {
      s.palabrasPorPrefijo(parametro);
    } else if (comando == "palabras_por_sufijo") {
      s.palabrasPorSufijo(parametro);
    } else if (comando == "posibles_palabras") {
      s.posiblesPalabras(parametro);
    } else {
      cout << "Comando no reconocido" << endl;
    }
  } else if (cantidadPalabras == 1 && parametro.empty() && comando != "ayuda" && comando != "grafo_de_palabras" && comando != "salir"){
    cout << "Comando sin parámetro o comando no reconocido" << endl;
  } else if (cantidadPalabras > 2 && !parametro.empty()) {
    cout << "Comando con más de un parámetro" << endl;
  }
}

void ayuda() {
  cout << "Comandos disponibles:" << endl;
  cout << endl;
  cout << "inicializar <diccionario.txt> " << endl;
  cout << "iniciar_inverso <diccionario.txt>" << endl;
  cout << "puntaje <palabra>" << endl;
  cout << "iniciar_arbol <diccionario.txt> " << endl;
  cout << "iniciar_arbol_inverso <diccionario.txt>" << endl;
  cout << "palabras_por_prefijo <prefijo>" << endl;
  cout << "palabras_por_sufijo <sufijo>" << endl;
  cout << "grafo_de_palabras" << endl;
  cout << "posibles_palabras <letras>" << endl;
  cout << "salir" << endl;
}

void ayudaConParametro(string comando){
  if(comando == "inicializar") {
    cout << "Comando: inicializar <diccionario.txt> \nInicializa el sistema a partir del archivo indicado." << endl;
  }else if(comando == "iniciar_inverso") {
    cout << "Comando: iniciar_inverso <diccionario.txt> \nInicializa el sistema a partir del archivo indicado en sentido inverso." << endl;
  }else if(comando == "puntaje") {
    cout << "Comando: puntaje <palabra> \nPermite conocer la puntuación que puede obtenerse con la palabra dada." << endl;
  }else if(comando == "iniciar_arbol") {
    cout << "Comando: iniciar_arbol <diccionario.txt> \nInicializa el sistema a partir del archivo indicado. A diferencia del comando inicializar, este comando almacena las palabras en uno o más árboles de letras." << endl;
  }else if(comando == "iniciar_arbol_inverso") {
    cout << "Comando: iniciar_arbol_inverso <diccionario.txt> \n A diferencia de los comandos iniciar_inverso e iniciar_arbol, este comando almacena las palabras en uno o más árboles de letras, pero en sentido inverso (leídas de derecha a izquierda)." << endl;
  }else if(comando == "palabras_por_prefijo") {
    cout << "Comando: palabras_por_prefijo <prefijo> \n Dado un prefijo de pocas letras, el comando recorre el(los) árbol(es) de letras (construído(s) con el comando iniciar_arbol) para ubicar todas las palabras posibles a construir a partir de ese prefijo." << endl;
  }else if(comando == "palabras_por_sufijo") {
    cout << "Comando: palabras_por_sufijo <sufijo> \nDado un sufijo de pocas letras, el comando recorre el(los) árbol(es) de letras construído(s) con el comando iniciar_arbol_inverso para ubicar todas las palabras posibles a construir que terminan con ese sufijo." << endl;
  }else if(comando == "grafo_de_palabras") {
    cout << "Comando: grafo_de_palabras \nCon las palabras ya almacenadas en el diccionario (luego de ejecutar el comando inicializar), el comando construye un grafo de palabras" << endl;
  }else if(comando == "posibles_palabras") {
    cout << "Comando: posibles_palabras <letras> \nDadas ciertas letras en una cadena de caracteres (sin importar su orden), el comando debe presentar en pantalla todas las posibles palabras válidas a construir" << endl;
  } else if(comando == "salir") {
      cout << "Comando: salir \nFinaliza la ejecución del programa. " << endl;
    }
    else{cout << "Comando no reconocido" << endl;}
}