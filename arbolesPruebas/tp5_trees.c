#include "tp_arboles.h"
#include <math.h>


//ALTURA del ÁRBOL

void a_alturaSub(ArbolBinario a, NodoArbol n, int cantidad, int *altura){

    if(n==NULL){
        if(cantidad>*altura){
            *altura=cantidad;}
            }
    else{
        a_alturaSub(a,n_hijoizquierdo(n),cantidad+1,altura);
        a_alturaSub(a,n_hijoderecho(n),cantidad+1,altura);
    }

}

int a_altura(ArbolBinario A){

    int altura=0;
    a_alturaSub(A,a_raiz(A),0,&altura);
    return altura;

}


//TRABAJO PRÁCTICO 5

//################## Ejercicio 2. #################################

//a. Hallar los Nodos HOJAS (NO TIENEN HIJOS)

void lDeHojas(ArbolBinario arbol, NodoArbol nodo, Lista lista){

    TipoElemento elemento=te_crear(0);
    //1. Base o Corte
    if (nodo==NULL){
        return;
    }

    //2. Recursivo
    else{
        if (n_hijoizquierdo(nodo)==NULL && n_hijoderecho(nodo)==NULL){ //COMPARACIÓN
            elemento=n_recuperar(nodo); //Recupera el TIPOELEMENTO del NODO 
            l_agregar(lista,elemento); //Lo AGREGA a la LISTA
            }

        //RECORRIDO (BINARIO: 2 HIJOS)
        //Regla: NO PUEDEN EXISTIR DOS "RETURN" 
        lDeHojas(arbol,n_hijoizquierdo(nodo),lista);
        lDeHojas(arbol,n_hijoderecho(nodo),lista);

        }

}


Lista listaDeHojas(ArbolBinario arbol){

    //FUNCIÓN Y SUB-FUNCIÓN
    //Utilizamos una FUNCIÓN para INICIAR LA SUB-FUNCIÓN con el NODO RAÍZ
    //SOLO para la PRIMERA INSTANCIA.

    Lista lista=l_crear();
    lDeHojas(arbol,a_raiz(arbol),lista);
    return lista;

}


//b. NODOS INTERIORES (NO RAICES, NO HOJAS)

bool esHoja(NodoArbol nodo){

    bool hoja=false;
    if (n_hijoizquierdo(nodo)==NULL && n_hijoderecho(nodo)==NULL){
       hoja=true;
    }
    return hoja;

}

void lDeNInteriores(ArbolBinario arbol, NodoArbol nodo, Lista lista){

    TipoElemento elemento;
    //Base
    if (nodo==NULL){}

    //Recursivo
    else{
        if (!(esHoja(nodo)) && nodo!=a_raiz(arbol)){
            elemento=n_recuperar(nodo);
            l_agregar(lista,elemento);
        }

        lDeNInteriores(arbol,n_hijoizquierdo(nodo),lista); //RECORRE por HIJO IZQUIERDO
        lDeNInteriores(arbol,n_hijoderecho(nodo),lista); //y RECORRE por HIJO DERECHO

    }

}

Lista listaDeNInteriores(ArbolBinario arbol){

    Lista lista=l_crear();
    lDeNInteriores(arbol,a_raiz(arbol),lista);
    return lista;

}

//#############################################################################


//Ejercicio 3.

//a.

void nodo_padre_sub(ArbolBinario a, NodoArbol n, int clave, TipoElemento *elemento){

    if(n==NULL){}

    else{
        /*if(hi->clave==clave || hd->clave==clave){
            elemento=n_recuperar(n);
            } ERROR! NO se pueden COMPARAR DATOS NULL CON DATOS PRIMITIVOS (EJ: NULL Y ENTEROS)*/
        TipoElemento hi=n_recuperar(n_hijoizquierdo(n));
        TipoElemento hd=n_recuperar(n_hijoderecho(n));
        if((hi!=NULL && hi->clave==clave) || (hd!=NULL && hd->clave==clave)){
            *elemento=n_recuperar(n);
        }

        nodo_padre_sub(a,n_hijoizquierdo(n),clave,elemento);
        nodo_padre_sub(a,n_hijoderecho(n),clave,elemento);

    }


}

TipoElemento nodo_padre(ArbolBinario A, int clave){

    TipoElemento e=te_crear(0);
    nodo_padre_sub(A,a_raiz(A),clave,&e);
    return e;

}

//d.

void nivelNodoSub(ArbolBinario a, NodoArbol n, int clave, int cantidad, int *nivel){

    if(n==NULL){}

    else{
        if(n_recuperar(n)->clave==clave){
            *nivel=cantidad;
        }

        nivelNodoSub(a,n_hijoizquierdo(n),clave,cantidad+1,nivel);
        nivelNodoSub(a,n_hijoderecho(n),clave,cantidad+1,nivel);
    }


}

int nivelNodo(ArbolBinario A, int clave){

    int nivel=0;
    nivelNodoSub(A,a_raiz(A),clave,0,&nivel);
    return nivel;

}


//e.

void a_altura_subarbolSub2(ArbolBinario a, NodoArbol nodo_actual, int cantidad, int *altura){

    if(nodo_actual==NULL){
        if(cantidad>*altura){
            *altura=cantidad;
        }
    }

    else{
        a_altura_subarbolSub2(a,n_hijoizquierdo(nodo_actual),cantidad+1,altura);
        a_altura_subarbolSub2(a,n_hijoderecho(nodo_actual),cantidad+1,altura);
    }

}


void a_altura_subarbolSub(ArbolBinario a, NodoArbol n, int clave, int *altura){

    if(n==NULL){}

    else{
        if(n_recuperar(n)->clave==clave){
            a_altura_subarbolSub2(a,n,0,altura);
        }

        a_altura_subarbolSub(a,n_hijoizquierdo(n),clave,altura);
        a_altura_subarbolSub(a,n_hijoderecho(n),clave,altura);
    }

}


int a_altura_subarbol(ArbolBinario A, int clave){

    int altura_subarbol=0;
    a_altura_subarbolSub(A,a_raiz(A),clave,&altura_subarbol);
    return altura_subarbol;

}

//#############################################################################


//Ejercicio 4.

//b.

void cantidad_hojas_N_ArioSub(ArbolBinario a, NodoArbol n, int *cantidad){

    if(n==NULL){}

    else{
        if(n_hijoizquierdo(n)==NULL){
            *cantidad=*cantidad+1;
        }
        cantidad_hojas_N_ArioSub(a,n_hijoizquierdo(n),cantidad);
        cantidad_hojas_N_ArioSub(a,n_hijoderecho(n),cantidad);
    }


}

int cantidad_hojas_N_Ario(ArbolBinario A){

    int cantidad=0;
    cantidad_hojas_N_ArioSub(A,a_raiz(A),&cantidad); //COMENZAMOS por el NODO RAIZ del ÁRBOL
    return cantidad;

}

//Determinar la cantidad de NODOS INTERIORES del árbol n-ario

void cantidad_nodos_intSub(ArbolBinario a, NodoArbol n, int *cantidad){

    if(n==NULL){}

    else{
        if(n_hijoizquierdo(n)!=NULL && n!=a_raiz(a)){
            *cantidad=*cantidad+1;
        }

        cantidad_nodos_intSub(a,n_hijoizquierdo(n),cantidad);
        cantidad_nodos_intSub(a,n_hijoderecho(n),cantidad);
    }


}

int cantidad_nodos_int(ArbolBinario A){

    int cantidad=0;
    cantidad_nodos_intSub(A,a_raiz(A),&cantidad);
    return cantidad;

}

//Determinar la cantidad de NODOS con 2 o más HIJOS

void NodosDosMasHijosSub(ArbolBinario a, NodoArbol n, int *cantidad){

    if(n==NULL){}

    else{

        if(n_hijoizquierdo(n)!=NULL && n_hijoderecho(n_hijoizquierdo(n))!=NULL){
            *cantidad=*cantidad+1;
        }
        NodosDosMasHijosSub(a,n_hijoizquierdo(n),cantidad);
        NodosDosMasHijosSub(a,n_hijoderecho(n),cantidad);

    }


}

int NodosDosMasHijos(ArbolBinario A){

    int cantidad=0;
    NodosDosMasHijosSub(A,a_raiz(A),&cantidad);
    return cantidad;

}


//d.


void nodo_Hijo_DerechoSub(ArbolBinario a, NodoArbol n, int clave, bool *hermano){

    if(n==NULL){}

    else{
        TipoElemento hd=n_recuperar(n_hijoderecho(n));
        if(hd!=NULL && hd->clave==clave){
            *hermano=true;
        }

        nodo_Hijo_DerechoSub(a,n_hijoderecho(n),clave,hermano);
    }

}


void nodo_Padre_N_ArioSub(ArbolBinario a, NodoArbol n, int clave, TipoElemento *elemento){


    if(n==NULL){}

    else{
        TipoElemento hi=n_recuperar(n_hijoizquierdo(n));
        if(hi!=NULL){

            if(hi->clave==clave){
                *elemento=n_recuperar(n);
            }

            else{
                bool hermano=false;
                nodo_Hijo_DerechoSub(a,n_hijoizquierdo(n),clave,&hermano);
                if(hermano){
                    *elemento=n_recuperar(n);
                }
            }
        }

        //Recorremos el ARBOL POR COMPLETO
        nodo_Padre_N_ArioSub(a,n_hijoizquierdo(n),clave,elemento);
        nodo_Padre_N_ArioSub(a,n_hijoderecho(n),clave,elemento);

    }


}


TipoElemento nodo_Padre_N_Ario(ArbolBinario A, int clave){

    TipoElemento elemento=te_crear(0);
    if(clave==n_recuperar(a_raiz(A))->clave){
        elemento=n_recuperar(a_raiz(A));
    }
    else{
        nodo_Padre_N_ArioSub(A,a_raiz(A),clave,&elemento);
    }
    return elemento;

}


//e.


void nodo_hermanos(ArbolBinario a, NodoArbol n, Lista hermanos){

    if(n==NULL){}

    else{
        TipoElemento hermano=n_recuperar(n);
        l_agregar(hermanos,hermano);

        nodo_hermanos(a,n_hijoderecho(n),hermanos);
    }

}

void lista_de_hermanosSub(ArbolBinario a, NodoArbol n, int clave, Lista hermanos){

    if(n==NULL){}

    else{
        TipoElemento hi=n_recuperar(n_hijoizquierdo(n));
        if(hi!=NULL && hi->clave==clave){
            nodo_hermanos(a,n_hijoizquierdo(n),hermanos);
        }

        else{
            bool hermano=false;
            nodo_Hijo_DerechoSub(a,n_hijoizquierdo(n),clave,&hermano);
            if(hermano){
                nodo_hermanos(a,n_hijoizquierdo(n),hermanos);
            }
        }

        lista_de_hermanosSub(a,n_hijoizquierdo(n),clave,hermanos);
        lista_de_hermanosSub(a,n_hijoderecho(n),clave,hermanos);

    }

}

Lista lista_de_hermanos(ArbolBinario A, int clave){

    Lista hermanos=l_crear();
    lista_de_hermanosSub(A,a_raiz(A),clave,hermanos);
    l_borrar(hermanos,clave);
    return hermanos;

}

//Ejercicio 7.

void arbolesEquivalentesSub(NodoArbol nodo, NodoArbol nodo2, bool *e){


    if(nodo==NULL || nodo2==NULL){
        if((nodo==NULL && nodo2!=NULL) || (nodo!=NULL && nodo2==NULL)){
            *e=false;
        }
        else{}
    }

    else if(*e){

        if(n_recuperar(nodo)->clave!=n_recuperar(nodo2)->clave){
            *e=false;
        }

        arbolesEquivalentesSub(n_hijoizquierdo(nodo),n_hijoizquierdo(nodo2),e);
        arbolesEquivalentesSub(n_hijoderecho(nodo),n_hijoderecho(nodo2),e);
    }


}

bool arbolesEquivalentes(ArbolBinario A, ArbolBinario B){

    bool e=true;
    arbolesEquivalentesSub(a_raiz(A),a_raiz(B),&e);
    return e;

}

//Ejercicio 8.

//a.

void a_altura_NarioSub(ArbolBinario a, NodoArbol n, int cantidad, int *altura){

    if(n==NULL){
        if(cantidad>*altura){
            *altura=cantidad;
        }
    }

    else{
        a_altura_NarioSub(a,n_hijoizquierdo(n),cantidad+1,altura);
        a_altura_NarioSub(a,n_hijoderecho(n),cantidad,altura);
    }


}

int a_altura_Nario(ArbolBinario A){

    int altura=0;
    a_altura_NarioSub(A,a_raiz(A),0,&altura);
    return altura;

}


//b.

void nivelNodoNarioSub(ArbolBinario a, NodoArbol n, int clave, int cantidad, int *nivel){

    if(n==NULL){}

    else{
        if(n_recuperar(n)->clave==clave){
            *nivel=cantidad;
        }

        nivelNodoNarioSub(a,n_hijoizquierdo(n),clave,cantidad+1,nivel);
        nivelNodoNarioSub(a,n_hijoderecho(n),clave,cantidad,nivel);

    }

}

int nivelNodoNario(ArbolBinario A, int clave){

    int nivel=0;
    nivelNodoNarioSub(A,a_raiz(A),clave,0,&nivel);
    return nivel;

}


//################## Ejercicios adicionales. #################################

//ARBOL LLENO

bool es_a_lleno(ArbolBinario A){

    bool lleno=false;
    int cantidad=pow(2,a_altura(A))-1;
    if(cantidad==a_cantidad_elementos(A)){
        lleno=true;
    }

    return lleno;

}

//LISTAS, TABLAS HASH Y ARBOLES

//Leemos un árbol que contiene desde los años 1990 hasta 1999. Lo guardamos en una Tabla Hash (por f. de Plegamiento)
//y luego lo recuperamos ordenadamente dentro de una Lista.

/*
void arbolDecada90Sub(ArbolBinario A, NodoArbol N, TablaHash P){

    if(N==NULL){}

    else{
        TipoElemento E=n_recuperar(N);
        th_insertar(P,E);

        arbolDecada90Sub(A,n_hijoizquierdo(N),P);
        arbolDecada90Sub(A,n_hijoderecho(N),P);
    }

}

void arbolDecada90(ArbolBinario A, TablaHash P){

    arbolDecada90Sub(A,a_raiz(A),P);

}


void insertarLista(TablaHash T, Lista L){

    for(int i=1990; i<=1999; i++){

        TipoElemento E=th_recuperar(T,i);
        l_agregar(L,E);

    }


}


int hash_por_modulo(int clave){

    return clave%10;

}
*/

//ES ARBOL BINARIO DE BUSQUEDA (RECORRIDO IN-ORDEN)

void esArbolBBSub(ArbolBinario arbol, NodoArbol nodo, NodoArbol pre, int i, bool *abb){

    //In-Orden
    if(nodo==NULL){}

    else{
        esArbolBBSub(arbol,n_hijoizquierdo(nodo),nodo,-1,abb);

        //Si el recorrido es por IZQUIERDA...
        if(i==-1){
            if(n_recuperar(nodo)->clave>n_recuperar(pre)->clave){
                *abb=false;
            }
        }
        //Si el recorrido es por DERECHA...
        else if(i==1){
            if(n_recuperar(nodo)->clave<n_recuperar(pre)->clave){
                *abb=false;
            }
        }

        esArbolBBSub(arbol,n_hijoderecho(nodo),nodo,1,abb);
    }


}

bool esArbolBB(ArbolBinario A){

    bool abb=true;
    esArbolBBSub(A,a_raiz(A),NULL,0,&abb);
    return abb;

}


//ARBOLES SIMILARES

void arbolesSimilaresSub(NodoArbol nodo, NodoArbol nodo2, bool *simil){


    if(nodo==NULL || nodo2==NULL){
        if((nodo==NULL && nodo2!=NULL) || (nodo!=NULL && nodo2==NULL)){
            *simil=false;
        }
        else{}
    }

    else if(*simil){
        arbolesSimilaresSub(n_hijoizquierdo(nodo),n_hijoizquierdo(nodo2),simil);
        arbolesSimilaresSub(n_hijoderecho(nodo),n_hijoderecho(nodo2),simil);
    }


}

bool arbolesSimilares(ArbolBinario A, ArbolBinario B){

    bool simil=true;
    arbolesSimilaresSub(a_raiz(A),a_raiz(B),&simil);
    return simil;

}


//ARBOLES N-ARIOS

void nivelSub3(NodoArbol nodo, Lista lista){

    if(nodo==NULL){}

    else{
        l_agregar(lista,n_recuperar(nodo));
        nivelSub3(n_hijoderecho(nodo),lista);
    }

}


void nivelSub2(NodoArbol nodo, Lista lista){

    if(nodo==NULL){}

    else{
        nivelSub3(n_hijoizquierdo(nodo),lista);
        nivelSub2(n_hijoderecho(nodo),lista);
    }

}


void nivelSub(NodoArbol nodo, int nivel, int cantidad, Lista lista, bool *listo){


    if(nodo==NULL){}
        
    else{

        if(cantidad==nivel-1){
            nivelSub2(nodo,lista);
            *listo=true;
        }
        
        if(!*listo){
            nivelSub(n_hijoizquierdo(nodo),nivel,cantidad+1,lista,listo);
            nivelSub(n_hijoderecho(nodo),nivel,cantidad,lista,listo);
        }
        
    }


}


Lista nivel(ArbolBinario A, int nivel){

    Lista l=l_crear();
    bool listo=false;
    //IMPORTANTE! Debemos VALIDAR los DATOS DE ENTRADA.
    if(nivel<0){}

    else if(nivel==0){
        l_agregar(l,n_recuperar(a_raiz(A)));
    }
    else{
        nivelSub(a_raiz(A),nivel,0,l,&listo);
    }
    return l;

}




int main(){

ArbolBinario a, b;
TipoElemento x;
NodoArbol N;

printf("Creando el Arbol Binario Vacio (Tamanio = 10) !\n");

//Creo el arbol
a = a_crear();
//b = a_crear();
cargar_arbol_binario(a); //Lo cargo


//MOSTRAR el ARBOL en PRE-ORDEN
printf("-----------------------------------------------------\n");
printf("Pre-Orden Desde la raiz\n");
pre_orden(a_raiz(a));
printf("\n");
//printf("Es Arbol BB: %d",esArbolBB(a));
//printf("Son similares: %d",arbolesSimilares(a,b));
//printf("\n");
//printf("Son equivalentes: %d",arbolesEquivalentes(a,b));
l_mostrarLista(nivel(a,2));




}