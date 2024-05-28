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
void recorrida(NodoArbol nodo, Lista lista){
    TipoElemento clave = te_crear(0);
    if (nodo==NULL){
        return;
    }
    
    if (n_hijoizquierdo(nodo) != NULL){
        clave = n_recuperar(nodo)->clave;
        l_agregar(lista, clave);
    }
    if (n_hijoderecho(nodo) != NULL){
        clave = n_recuperar(nodo)->clave;
        l_agregar(lista, clave);
    }
    recorrida(n_hijoizquierdo(nodo), lista);
    recorrida(n_hijoderecho(nodo), lista);
}
Lista a_ej4_anchura(ArbolBinario A){
    Lista lista = l_crear();
    recorrida(a_raiz(A), lista);
    return lista;
}

// b.	Escribir una función que, dado un árbol n-ario, devuelva el número (cantidad) de hojas de dicho árbol.
int a_ej4_q_hojas(ArbolBinario A);
int cantidadHojas(NodoArbol nodo, int *cantidad){
    if (nodo == NULL)
    {
        return;
    }
    if (n_hijoizquierdo(nodo) == NULL || n_hijoderecho(nodo) == NULL)
    {
        *cantidad++;
    }
    
    cantidadHojas(n_hijoizquierdo(nodo), *cantidad);
    cantidadHojas(n_hijoderecho(nodo), *cantidad);
    
}
int a_ej4_q_hojas(ArbolBinario A){
    int cantidad = 0;
    cantidadHojas(a_raiz(A), &cantidad);
    return cantidad;
}

// c.	Escribir una función booleana que dados dos árboles generales determine si tienen la misma estructura, sin importar los datos del mismo (árbol similar).
bool a_ej4_similares(ArbolBinario A, ArbolBinario B);
bool equiparar(NodoArbol nodoa, NodoArbol nodob, bool *igualdad){
    if (nodoa == NULL && nodob == NULL)
    {
        *igualdad = true;
    }
    {
    if (n_hijoizquierdo(nodoa) == NULL && n_hijoderecho(nodob) != NULL || n_hijoizquierdo(nodoa) != NULL && n_hijoderecho(nodob) == NULL)
        *igualdad = false;
    }
    equiparar(n_hijoizquierdo(nodoa), n_hijoizquierdo(nodob), igualdad);
    equiparar(n_hijoderecho(nodoa), n_hijoderecho(nodob), igualdad);
    
}

bool a_ej4_similares(ArbolBinario A, ArbolBinario B){
    bool igualdad = true;
    equiparar(a_raiz(A), a_raiz(B), &igualdad);
}

// d.	Retornar el padre de un nodo del árbol (tipo_elemento).
TipoElemento a_ej4_padre(ArbolBinario A, int clave);


// e.	Retornar los hermanos de un nodo del árbol (lista de hermanos).
Lista a_ej4_hermanos(ArbolBinario A, int clave);