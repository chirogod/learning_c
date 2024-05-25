
#include "tp_arboles.h"//

//FUNCIONES ÚTILES PARA LA IMPLEMENTACIÓN DE ARBOLES BINARIOS

ArbolBinario a_cargarArbol(ArbolBinario a);

ArbolBinario a_cargarArbol(ArbolBinario a){

    TipoElemento e=te_crear(14);
    //Me paro en el nodo raíz (INICIO)
    NodoArbol nodo=a_conectar_hi(a,a_raiz(a),e);
    a_cargarArbol(a,nodo,e);    


}

/*
0: El nuevo nodo (con su TE) se asignará a la raíz de A. En este caso N no es utilizado.
-1: El nuevo nodo (con su TE) se enlazará como hijo izquierdo de N.
1: El nuevo nodo (con su TE) se enlazará como hijo derecho de N.
*/
void Cargar_SubArbol(ArbolBinario A, NodoArbol N, int subarbol){
    TipoElemento X;
    NodoArbol N1;
    int n;
    bool b;
    if(!a_es_lleno(A)){
        b= ingresoEntero(&n); //INGRESO un número entero
        if (b){
            X= te_crear(n);
            
            if(subarbol == -1){
                N1 = a_conectar_hi(A, N, X);
                }
            else if(subarbol == 1){
                N1 = a_conectar_hd(A, N, X);
                }
            else {
                N1 = a_establecer_raiz(A, X);
                }

            Cargar_SubArbol(A, N1, -1);
            Cargar_SubArbol(A, N1, 1);
        }
    }    
}

/*Función que recibe el árbol a ser cargado y llama a la función recursiva que realiza
la carga nodo por nodo*/
void cargar_arbol_binario(ArbolBinario A){
    Cargar_SubArbol(A, NULL, 0);
}
