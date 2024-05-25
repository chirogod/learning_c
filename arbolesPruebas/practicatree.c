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
    //primero equiparar nodos
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
    ArbolBinario arbolb = a_crear();
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

    // Inserto la Raiz
    elemento = te_crear(8);
    a_establecer_raiz(arbolb, elemento);

    elemento = te_crear(6);
    nodo = a_conectar_hi(arbolb, a_raiz(arbolb), elemento);

    elemento = te_crear(5);
    a_conectar_hi(arbolb, nodo, elemento);

    elemento = te_crear(7);
    a_conectar_hd(arbolb, nodo, elemento);

    elemento = te_crear(13);
    nodo = a_conectar_hd(arbolb, a_raiz(arbolb), elemento);

    elemento = te_crear(9);
    a_conectar_hi(arbolb, nodo, elemento);

    elemento = te_crear(11);
    a_conectar_hd(arbolb, nodo, elemento);
    // Print the tree structure
    printf("-----------------------------------------------------\n");
    printf("Arbol Binario b:\n");
    print_arbol(a_raiz(arbolb), 0);
    printf("-----------------------------------------------------\n");

    bool equivalentes = a_ej7_equivalente(arbol, arbolb);
    if (equivalentes) {
        printf("Los arboles son equivalentes.\n");
    } else {
        printf("Los arboles no son equivalentes.\n");
    }
}