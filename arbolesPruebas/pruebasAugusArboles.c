#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_arboles.h"
#define COUNT 10

int altura(ArbolBinario A);
void hojas(ArbolBinario A);
void print_arbol(NodoArbol root, int space);
int imprimirRaiz(ArbolBinario A);



// Function to print binary tree in a 2D structure
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

//Muestra el arbol a partir de un nodo (de ahi hacia abajo)
void pre_orden(NodoArbol N){
    TipoElemento x;
    if (N == NULL) {
        printf(".");
    }
    else {
        x = n_recuperar(N);
        printf(" %d", x->clave);
        pre_orden(n_hijoizquierdo(N));
        pre_orden(n_hijoderecho(N));
    }
}

//Muestra el arbol a partir de un nodo (de ahi hacia abajo)
void in_orden(NodoArbol N){
    TipoElemento x;
    if (N == NULL) {
        printf(".");
    }
    else {
        in_orden(n_hijoizquierdo(N));
        x = n_recuperar(N);
        printf(" %d", x->clave);
        in_orden(n_hijoderecho(N));
    }
}

//Muestra el arbol a partir de un nodo (de ahi hacia abajo)
void post_orden(NodoArbol N){
    TipoElemento x;
    if (N == NULL) {
        printf(".");
    }
    else {
        post_orden(n_hijoizquierdo(N));
        post_orden(n_hijoderecho(N));
        x = n_recuperar(N);
        printf(" %d", x->clave);
    }
}

int imprimirRaiz(ArbolBinario A){
    printf("La raiz del arbol es:   %d",a_raiz(A)->datos->clave);
}

int main()
{
    ArbolBinario a;
    TipoElemento x;
    NodoArbol N;

    printf("Creando el Arbol Binario Vacio (Tamano = 10) !\n");
    a = a_crear();

    if (a_es_vacio(a)) {
        printf("El arbol esta vacio !\n");
    }

    // Inserto la Raiz
    x = te_crear(5);
    a_establecer_raiz(a, x);
    printf("Cantidad de Nodos: %d \n", a_cantidad_elementos(a));

    // Inserto uno por izquierda
    x = te_crear(3);
    a_conectar_hi(a, a_raiz(a), x);
    printf("Cantidad de Nodos: %d \n", a_cantidad_elementos(a));

    // Inserto uno por derecha
    x = te_crear(8);
    N = a_conectar_hd(a, a_raiz(a), x);
    printf("Cantidad de Nodos: %d \n", a_cantidad_elementos(a));

    // Inserto uno por derecha
    x = te_crear(10);
    N = a_conectar_hd(a, N, x);
    printf("Cantidad de Nodos: %d \n", a_cantidad_elementos(a));

    // Inserto uno por derecha
    x = te_crear(15);
    a_conectar_hd(a, N, x);
    printf("Cantidad de Nodos: %d \n", a_cantidad_elementos(a));

    // Inserto uno por derecha
    x = te_crear(13);
    N = a_conectar_hi(a, N, x);
    printf("Cantidad de Nodos: %d \n", a_cantidad_elementos(a));

    // Inserto uno por derecha
    x = te_crear(14);
    a_conectar_hi(a, NULL, x);
    printf("Cantidad de Nodos: %d \n", a_cantidad_elementos(a));

    // LLamo al mostrar arbol
    printf("-----------------------------------------------------\n");
    printf("Pre-Orden Desde la raiz\n");
    pre_orden(a_raiz(a));
    printf("\n");
    printf("-----------------------------------------------------\n");
    printf("In-Orden Desde la raiz\n");
    in_orden(a_raiz(a));
    printf("\n");
    printf("-----------------------------------------------------\n");
    printf("Post-Orden Desde la raiz\n");
    post_orden(a_raiz(a));
    printf("\n");

    printf("-----------------------------------------------------\n");
    printf("Altura del Arbol: %d \n", altura(a));
    printf("-----------------------------------------------------\n");

    hojas(a);

    // Print the tree structure
    printf("-----------------------------------------------------\n");
    printf("Arbol Binario:\n");
    print_arbol(a_raiz(a), 0);
    printf("-----------------------------------------------------\n");


    imprimirRaiz(a);
}



//---------------------------------------------------------
//Calcula la Altura del Arbol
//---------------------------------------------------------
// Funcion que realmente calcula la altura
void altint(NodoArbol Q, int *h, int c){
    if (Q == NULL) {
        if (c > *h) {
            *h = c;
        }
    }
    else {
        altint(n_hijoizquierdo(Q), h, c++);
        altint(n_hijoderecho(Q), h, c++);
    }
}
// funcion que llama a la que calcula la altura
int altura(ArbolBinario A){
    int alt = 0;
    altint(a_raiz(A), &alt, 0);
    return alt;
}

// imprime las hojas
void hojasint(NodoArbol Q){
    TipoElemento x;

    if (Q == NULL) {
    }
    else {
        // averigua si es un hoja
        if ((n_hijoizquierdo(Q) == NULL) && (n_hijoderecho(Q) == NULL)) {
            x = n_recuperar(Q);
            printf("Hoja: %d \n",  x->clave);
        }
        // Llamo para el recorrido
        hojasint(n_hijoizquierdo(Q));
        hojasint(n_hijoderecho(Q));
    }
}
void hojas(ArbolBinario A){
    hojasint(a_raiz(A));
};