#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_arboles.h"
#define COUNT 10

/**
2.	Dado un árbol binario no vacío determinar:  
 */

//  a.	Retornar una lista con todos los nodos terminales u hojas.
Lista a_ej2_hojas(ArbolBinario A);

void hojas(ArbolBinario arbol, NodoArbol nodo, Lista lista){
    TipoElemento hoja = te_crear(0);
    if (nodo == NULL){
        return;
    }
    
    if (n_hijoizquierdo(nodo) == NULL && n_hijoderecho(nodo) == NULL)
    {
        hoja = n_recuperar(nodo);
        l_agregar(lista, hoja);
    }
    hojas(arbol,n_hijoizquierdo(nodo),lista);
    hojas(arbol,n_hijoderecho(nodo),lista);
    
}

Lista a_ej2_hojas(ArbolBinario A){
    Lista lista = l_crear();
    hojas(A,a_raiz(A),lista);
    l_mostrar(lista);
}

//  b.	Retornar en una estructura todos los nodos interiores (los que no son ni hojas ni raíz)
Lista a_ej2_interiores(ArbolBinario A);
void nodosInteriores(ArbolBinario arbol, NodoArbol nodo, Lista lista){
    TipoElemento nodoInterior;
    if (nodo == NULL){
        return;
    }
    if (nodo != a_raiz(arbol) && n_hijoizquierdo(nodo) != NULL || n_hijoderecho(nodo) != NULL){
        nodoInterior = n_recuperar(nodo);
        l_agregar(lista, nodoInterior);
    }
    nodosInteriores(arbol, n_hijoderecho(nodo), lista);
    nodosInteriores(arbol, n_hijoizquierdo(nodo), lista);
    
    
}

Lista a_ej2_interiores(ArbolBinario A){
    Lista listaNodoInteriores = l_crear();
    nodosInteriores(A, a_raiz(A), listaNodoInteriores);
    l_mostrar(listaNodoInteriores);
}

//  c.	Buscar todas las ocurrencias de una clave dentro del árbol. Retornar la posición de cada ocurrencia (puntero al nodo).
Lista a_ej2_buscarclave(ArbolBinario A, int clave);

//no tengo idea que son las ocurrencias jaaaaaaaaaaaaaaaaa


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

    listaHojas(arbol);

}
    
