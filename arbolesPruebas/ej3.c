#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_arboles.h"
#define COUNT 10
/**
3.	Para un nodo del árbol binario determinado:
 */
    // a.	Indicar el nombre del nodo padre (clave).
int a_ej3_clavepadre(ArbolBinario A, int clavehijo);
NodoArbol padre(ArbolBinario A, NodoArbol nodo,  int clavehijo){
    if (nodo == NULL)
    {
        return;
    }
    if (n_hijoizquierdo(nodo->datos->clave) == clavehijo || n_hijoderecho(nodo->datos->clave) == clavehijo)
    {
        return nodo;
    }else{
        padre(A, n_hijoderecho(nodo), clavehijo);
        padre(A, n_hijoizquierdo(nodo), clavehijo); 
    }
      
}
int a_ej3_clavepadre(ArbolBinario A, int clavehijo){
    
    NodoArbol nodoPadre = padre(A, a_raiz(A), clavehijo);
    if (nodoPadre != NULL)
    {
        printf(nodoPadre->datos->valor);
    }
    
    
}
// b.	Listar los hijos (solo las clave/s).
Lista a_ej3_hijos(ArbolBinario A, int clavepadre);
void listarHijos(ArbolBinario A,NodoArbol nodo, int clavepadre, Lista listaHijos){
    TipoElemento hijo = te_crear(0);
    if (clavepadre != NULL){
        return "no existe";
    }
    if (nodo->datos->clave == clavepadre){
        if (n_hijoizquierdo(nodo) != NULL){
            hijo = n_hijoizquierdo(nodo->datos->clave);
            l_agregar(listaHijos,hijo);
        }
        if (n_hijoderecho(nodo) != NULL){
            hijo = n_hijoderecho(nodo->datos->clave);
            l_agregar(listaHijos,hijo);
        }
        
    }
    listarHijos(A, n_hijoderecho(nodo), clavepadre, listaHijos);
    listarHijos(A, n_hijoizquierdo(nodo), clavepadre, listaHijos);
    
}
Lista a_ej3_hijos(ArbolBinario A, int clavepadre){
    Lista lista = l_crear();
    listarHijos(A, a_raiz(A) ,clavepadre, lista);
    l_mostrar(lista);
    return lista;
    
}

// c.	Listar el hermano (solo la clave).
int a_ej3_hermano(ArbolBinario A, int clave);
void listarHermano(ArbolBinario A,NodoArbol nodo, int clave, Lista listaHermano){
    TipoElemento hermano = te_crear(0);
    if (clave != NULL){
        return "no existe";
    }
    if (n_hijoizquierdo(nodo) == clave){
        hermano = n_hijoderecho(nodo->datos->clave);
        l_agregar(listarHermano,hermano);
    }
    if (n_hijoderecho(nodo) == clave){
        hermano = n_hijoizquierdo(nodo->datos->clave);
        l_agregar(listarHermano,hermano);
    }

    listarHermano(A, n_hijoderecho(nodo), clave, listarHermano);
    listarHermano(A, n_hijoizquierdo(nodo), clave, listarHermano);

}
int a_ej3_hermano(ArbolBinario A, int clave){
    Lista lista = l_crear();
    listarHermano(A, a_raiz(A) ,clave, lista);
    l_mostrar(lista);
    return lista;

}


// d.	Calcular el nivel en el que se encuentra.
int a_ej3_nivel(ArbolBinario A, int clave);
void calcularNivel(ArbolBinario A, NodoArbol nodo, int *cantidad, int clave){
    if (clave != NULL)
    {
        return;
    }
    if (n_hijoizquierdo(nodo)->datos->clave == clave || n_hijoderecho(nodo)->datos->clave == clave){
        *cantidad++;
    }
    calcularNivel(A, n_hijoizquierdo, *cantidad, clave);
    calcularNivel(A, n_hijoderecho, *cantidad, clave);
    
}
int nivelNodo(ArbolBinario A, int clave){

    int cantidad=0;
    calcularNivel(A,a_raiz(A),&cantidad, clave);
    return cantidad;

}


// e.	Calcular la altura de su rama (Altura del Subárbol)
int a_ej3_alturarama(ArbolBinario A, int clave);

// f.	Listar todos los nodos que están en el mismo nivel (solo la clave).
Lista a_ej3_clavesmismonivel(ArbolBinario A, int nivel);

    
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
    a_ej3_clavepadre(arbol, 11);
}