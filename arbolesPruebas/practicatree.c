#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_arboles.h"
#define COUNT 10

/**
4.	Para Árboles “N-arios”:
 */
// b.	Escribir una función que, dado un árbol n-ario(que igual se carga de manera que es un n-ario transformado en binario) devuelva el número (cantidad) de hojas de dicho árbol.
int a_ej4_q_hojas(ArbolBinario A);
void cantidadHojas(NodoArbol nodo, int *cantidad){
    if (nodo == NULL)
    {
        return;
    }
    if (n_hijoizquierdo(nodo) == NULL && n_hijoderecho(nodo) == NULL)
    {
        (*cantidad)++;
    }
    
    cantidadHojas(n_hijoizquierdo(nodo), *cantidad);
    cantidadHojas(n_hijoderecho(nodo), *cantidad);
    
}
int a_ej4_q_hojas(ArbolBinario A){
    int cantidad = 0;
    cantidadHojas(a_raiz(A), &cantidad);
    return cantidad;
}


int main()
{
    ArbolBinario arbol = a_crear();
    ArbolBinario arbolb = a_crear();
    TipoElemento elemento;
    NodoArbol nodo;


    // Inserto la Raiz
    elemento = te_crear("m");
    a_establecer_raiz(arbol, elemento);

    elemento = te_crear("e");
    nodo = a_conectar_hi(arbol, a_raiz(arbol), elemento);

    elemento = te_crear("l");
    a_conectar_hd(arbol, nodo, elemento);

    elemento = te_crear("b");
    nodo =a_conectar_hi(arbol, nodo, elemento);

    elemento = te_crear("a");
    a_conectar_hi(arbol, nodo, elemento);

    elemento = te_crear("d");
    a_conectar_hd(arbol, nodo, elemento);

    elemento = te_crear("p");
    nodo = a_conectar_hd(arbol, a_raiz(arbol), elemento);

    elemento = te_crear("n");
    a_conectar_hi(arbol,nodo, elemento);

    elemento = te_crear("v");
    nodo = a_conectar_hd(arbol, nodo, elemento);

    elemento = te_crear("t");
    a_conectar_hi(arbol, nodo, elemento);

    elemento = te_crear("z");
    a_conectar_hd(arbol, nodo, elemento);


    // Print the tree structure
    printf("-----------------------------------------------------\n");
    printf("Arbol Binario:\n");
    print_arbol(a_raiz(arbol), 0);
    printf("-----------------------------------------------------\n");

    int hojas = a_ej4_q_hojas(arbol);
    printf("Cantidad de hojas del árbol: %d\n", hojas);

}