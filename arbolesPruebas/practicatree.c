#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_arboles.h"
#define COUNT 10
NodoArbol padre(ArbolBinario A, NodoArbol nodo, int clavehijo) {
    NodoArbol np = n_crear(0);
    if (nodo == NULL) {
        return NULL;
    }
    
    // ver si el hijo izq o el dere del nodo actual tiene la clave
    if ((n_hijoizquierdo(nodo) != NULL && n_hijoizquierdo(nodo)->datos->clave == clavehijo) || (n_hijoderecho(nodo) != NULL && n_hijoderecho(nodo)->datos->clave == clavehijo)) {
        np = n_recuperar(nodo);
        return np;
    }
    return padre(A, n_hijoizquierdo(nodo), clavehijo);
    return padre(A, n_hijoderecho(nodo), clavehijo);
}

int a_ej3_clavepadre(ArbolBinario A, int clavehijo) {
    NodoArbol nodoPadre = padre(A, a_raiz(A), clavehijo);
    if (nodoPadre != NULL) {
        printf("La clave del padre es: %d\n", nodoPadre->datos->clave);
        return nodoPadre->datos->clave;
    } else {
        printf("No se encontró un nodo padre para la clave %d\n", clavehijo);
        return -1; // or any other suitable error code
    }
}

void print_arbol(NodoArbol root, int space) {
    if (root == NULL)
        return;

    space += COUNT;

    print_arbol(n_hijoderecho(root), space);

    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->datos->clave);

    print_arbol(n_hijoizquierdo(root), space);
}


int main()
{
    ArbolBinario arbol = a_crear();
    TipoElemento elemento;
    NodoArbol nodo;


    // Inserto la Raiz
    elemento = te_crear(8);
    a_establecer_raiz(arbol, elemento);

    elemento = te_crear(6);
    nodo = a_conectar_hi(arbol, a_raiz(arbol), elemento);

    elemento = te_crear(5);
    a_conectar_hi(arbol, nodo, elemento);

    elemento = te_crear(7);
    a_conectar_hd(arbol, nodo, elemento);

    elemento = te_crear(10);
    nodo = a_conectar_hd(arbol, a_raiz(arbol), elemento);

    elemento = te_crear(9);
    a_conectar_hi(arbol, nodo, elemento);

    elemento = te_crear(11);
    a_conectar_hd(arbol, nodo, elemento);


    // Print the tree structure
    printf("-----------------------------------------------------\n");
    printf("Arbol Binario:\n");
    print_arbol(a_raiz(arbol), 0);
    printf("-----------------------------------------------------\n");

    a_ej3_clavepadre(arbol,9);

}