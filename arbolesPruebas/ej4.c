#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_arboles.h"
/**
4.	Para Árboles “N-arios”:
 */
// a.	Dado un árbol n-ario, devolver en forma de lista el resultado del recorrido en anchura del árbol  (solo las claves).
Lista a_ej4_anchura(ArbolBinario A);

// b.	Escribir una función que, dado un árbol n-ario, devuelva el número (cantidad) de hojas de dicho árbol.
int a_ej4_q_hojas(ArbolBinario A);

// c.	Escribir una función booleana que dados dos árboles generales determine si tienen la misma estructura, sin importar los datos del mismo (árbol similar).
bool a_ej4_similares(ArbolBinario A, ArbolBinario B);

// d.	Retornar el padre de un nodo del árbol (tipo_elemento).
TipoElemento a_ej4_padre(ArbolBinario A, int clave);

// e.	Retornar los hermanos de un nodo del árbol (lista de hermanos).
Lista a_ej4_hermanos(ArbolBinario A, int clave);
