#include "tp_arboles.h"
/**
9.Generar un algoritmo, recursivo o no, que permita construir un árbol binario de búsqueda balanceado (AVL) 
  a partir de un árbol binario sin un orden determinado.
  Comparar las alturas de ambos árboles. Determinar la complejidad algorítmica.
*/
// Primero llamamos para construir el AVL
ArbolAVL a_ej9_construiravl(ArbolBinario A);

// Luego con el resultado de la funcion anterior llamamos a una funcion para que nos retorne la diferencia de las alturas 
// comparadas como Altura(ArbolBinario) - Altura(ArbolAVL).
int a_ej9_diferenciaalturas(ArbolBinario A, ArbolAVL AVL);