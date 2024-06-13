#include "pilas.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tipo_elemento.h"

static const int TAMANIO_MAXIMO = 10;

struct PilaRep {
    TipoElemento *valores;
     int *tope;
};

Pila p_crear(){
    Pila nueva_pila = (Pila) malloc(sizeof(struct PilaRep));
    nueva_pila->tope = NULL;
    return nueva_pila;
}


void p_apilar (Pila pila, TipoElemento elemento) {
    int *nuevo_tope;
}
TipoElemento p_desapilar (Pila pila);
TipoElemento p_tope (Pila pila);

bool p_es_vacia (Pila pila) {
    return pila->tope == NULL;
}
bool p_es_llena (Pila pila);

void p_mostrar (Pila pila);