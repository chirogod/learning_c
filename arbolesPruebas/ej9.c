#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_arboles.h"
/**
9.Generar un algoritmo, recursivo o no, que permita construir un árbol binario de búsqueda balanceado (AVL) 
  a partir de un árbol binario sin un orden determinado.
  Comparar las alturas de ambos árboles. Determinar la complejidad algorítmica.
*/
// Primero llamamos para construir el AVL
ArbolAVL a_ej9_construiravl(ArbolBinario A);
void insertarAVL( ArbolAVL avl,NodoArbol nodo);
void insertarAVL( ArbolAVL avl, NodoArbol nodo){
  if (nodo == NULL)
  {
    return;
  }
  TipoElemento nodo = n_recuperar(nodo);
  avl_insertar(avl, nodo);
  
  insertarAVL(avl, n_hijoizquierdo(nodo));
  insertarAVL(avl, n_hijoderecho(nodo));
  
}

ArbolAVL a_ej9_construiravl(ArbolBinario A){
  ArbolAVL avl = avl_crear();
  insertarAVL(avl, a_raiz(A));
  
}


// Luego con el resultado de la funcion anterior llamamos a una funcion para que nos retorne la diferencia de las alturas 
// comparadas como Altura(ArbolBinario) - Altura(ArbolAVL).
int a_ej9_diferenciaalturas(ArbolBinario A, ArbolAVL AVL);
int a_ej9_diferenciaalturas(ArbolBinario A, ArbolAVL AVL){
  int alturaBinario = avl_altura_izq(a_raiz(A)) + avl_altura_der(a_raiz(A));
  int alturaAvl = avl_altura_izq(avl_raiz(AVL)) + avl_altura_der(avl_raiz(AVL));
  int diferencia = alturaBinario - alturaAvl;
  return diferencia;
}