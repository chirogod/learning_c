#include "tp_arboles.h"
/**
8.	Dado un árbol “n-ario” se pide:
 */
// a.	Determinar la altura del mismo.
int c_ej8_altura(ArbolBinario A);
void a_alturaSub(ArbolBinario a, NodoArbol n, int cantidad, int *altura){
    //si el nodo es nulo
    if(n==NULL){
        //si el numero que hay en cantidad es mayor al numero que hay en altura
        if(cantidad>*altura){
            //altura ahora tiene lo que tenia cantidad
            *altura=cantidad;}
    }
    a_alturaSub(a,n_hijoizquierdo(n),cantidad+1,altura);
    a_alturaSub(a,n_hijoderecho(n),cantidad+1,altura);

}

int c_ej8_altura(ArbolBinario A){

    int altura=0;
    a_alturaSub(A,a_raiz(A),0,&altura);
    return altura;

}

// b.	Determinar el nivel de un nodo.
int c_ej8_nivel(ArbolBinario A, int clave);
int calcNivel(NodoArbol nodo, int clave, int *nivel){
    if (nodo == NULL){
        return;
    }
    if (n_hijoizquierdo(nodo)->datos->clave != clave)
    {
        *nivel++;
    }else{
        return nivel;
    }
    calcNivel(n_hijoizquierdo(nodo), clave, &nivel);
    calcNivel(n_hijoderecho(nodo), clave, &nivel);
}
int c_ej8_nivel(ArbolBinario A, int clave){
    int nivel = 0;
    calcNivel(a_raiz(A), clave, &nivel);
}

// c.	Listar todos los nodos internos (solo las claves).
Lista c_ej8_internos(ArbolBinario A);
//si el nodo en recorrida no es raiz ni hoja listarlo
void encontrarInternos(ArbolBinario A, NodoArbol nodo, Lista lista){
    TipoElemento elemento = te_crear(0);
    if (nodo == NULL){
        return 0;
    }
    if (nodo != a_raiz(A) && n_hijoizquierdo(nodo) == NULL && n_hijoderecho(nodo) == NULL){  
        elemento = n_recuperar(nodo)->clave;
        l_agregar(lista, elemento);
    }
    encontrarInternos(A, n_hijoizquierdo(nodo), lista);
    encontrarInternos(A, n_hijoderecho(nodo), lista);
}

Lista c_ej8_internos(ArbolBinario A){
    Lista lista = l_crear();
    encontrarInternos(A, a_raiz(A), lista);
    return lista;
}

// d.	Determinar si todas las hojas están al mismo nivel.
bool c_ej8_hojasmismonivel(ArbolBinario A);
