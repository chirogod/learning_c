#include "tp_arboles.h"
/**
10.	Dada una serie de números generados al azar, cargar la misma serie en un árbol binario de búsqueda y en un árbol binario balanceado “AVL”.  
	Comparar la altura de ambos árboles.  
	Repetir el proceso “n” veces. 
	¿Qué puede concluir al respecto?
 */
// Generamos una lista con la seria de numeros
Lista a_ej10_generarlistaclaves(int cantidadclavesagenerar);

// Ahora se la paso a la funcion que crea los 2 arboles
ArbolBinarioBusqueda a_ej10_crearABB(Lista L);
ArbolAVL a_ej10_crearAVL(Lista L);

// Ahora llamos a la funcion que compara las alturas.  La comparacion es Altura(ABB) - Altura(AVL).
int a_ej10_difalturas(ArbolBinarioBusqueda ABB, ArbolAVL AVL);

// Este proceso se debera repetir N veces  (N se debera poder tomar por teclado).

// LLamada general del proceso.  retorna una lista con todas las diferencias de las comparaciones.
Lista a_ej10_comparacionarboles(int N_repeticiones);