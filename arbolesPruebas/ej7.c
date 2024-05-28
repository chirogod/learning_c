#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_arboles.h"
#define COUNT 10
/**
7.	Determinar si dos árboles binarios son equivalentes.
 */
bool a_ej7_equivalente(ArbolBinario A, ArbolBinario B);

bool equiparar(NodoArbol nodoa, NodoArbol nodob, bool *igualdad){
    if (nodoa == NULL && nodob == NULL) {
        return true;
    }
    // equiparar nodos
    if (n_recuperar(nodoa) == NULL && n_recuperar(nodob) != NULL || n_recuperar(nodoa) != NULL && n_recuperar(nodob) == NULL)
    {
        *igualdad = false;
    }
    if (n_recuperar(nodoa)->clave != n_recuperar(nodob)->clave)
    {
        *igualdad = false;
    }
    equiparar(n_hijoizquierdo(nodoa),n_hijoizquierdo(nodob),igualdad);
    equiparar(n_hijoderecho(nodoa),n_hijoderecho(nodob),igualdad);
}

bool a_ej7_equivalente(ArbolBinario A, ArbolBinario B){
    bool igualdad = true;
    equiparar(a_raiz(A), a_raiz(B), &igualdad);
    return igualdad;    
}