#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_arboles.h"
/**
10.	Dada una serie de números generados al azar, cargar la misma serie en un árbol binario de búsqueda y en un árbol binario balanceado “AVL”.  
	Comparar la altura de ambos árboles.  
	Repetir el proceso “n” veces. 
	¿Qué puede concluir al respecto?
 */
// Generamos una lista con la seria de numeros
Lista a_ej10_generarlistaclaves(int cantidadclavesagenerar);
Lista a_ej10_generarlistaclaves(int cantidadclavesagenerar){

	Lista lista = l_crear();
	TipoElemento numero = te_crear(0);
	for (int i = 0; i < cantidadclavesagenerar; i++){
		int numero = rand() % 11;
		l_agregar(lista, numero);
	}
	return lista;
	
	
}
// Ahora se la paso a la funcion que crea los 2 arboles
ArbolBinarioBusqueda a_ej10_crearABB(Lista L);
ArbolBinarioBusqueda a_ej10_crearABB(Lista L){
	Iterador iterador(L);
	ArbolBinarioBusqueda abb = abb_crear();
	while (hay_siguiente(iterador)) {
		TipoElemento elem = siguiente(iterador);
		abb_insertar(abb, elem);
	}
}
ArbolAVL a_ej10_crearAVL(Lista L);
ArbolAVL a_ej10_crearAVL(Lista L){
	Iterador iterador(L);
	ArbolAVL avl = avl_crear();
	while (hay_siguiente(iterador)) {
		TipoElemento elem = siguiente(iterador);
		abb_insertar(avl, elem);
	}
}

int altura(NodoArbol nodo, int *cantidad){
	if (n_hijoizquierdo(nodo) != NULL  || n_hijoderecho(nodo) != NULL){
		*cantidad++;
	}
	altura(n_hijoizquierdo(nodo), &cantidad);
	altura(n_hijoderecho(nodo), &cantidad);
	
}
// Ahora llamos a la funcion que compara las alturas.  La comparacion es Altura(ABB) - Altura(AVL).
int a_ej10_difalturas(ArbolBinarioBusqueda ABB, ArbolAVL AVL);
int a_ej10_difalturas(ArbolBinarioBusqueda ABB, ArbolAVL AVL){
	int cantidad = 0;
	int alturaABB = altura(ABB, cantidad);
	int alturaAVL = altura(AVL, cantidad);
	return alturaABB - alturaAVL;
}
// Este proceso se debera repetir N veces  (N se debera poder tomar por teclado).

// LLamada general del proceso.  retorna una lista con todas las diferencias de las comparaciones.
Lista a_ej10_comparacionarboles(int N_repeticiones);
