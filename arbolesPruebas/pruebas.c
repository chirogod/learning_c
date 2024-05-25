#include "nodo.h"
#include "arbol-avl.h"

static const int TAMANIO_MAXIMO = 1000;

NodoArbol avl_rotar_derecha(NodoArbol nodo);

NodoArbol avl_rotar_izquierda(NodoArbol nodo);

int avl_altura_izq(NodoArbol nodo);

int avl_altura_der(NodoArbol nodo);

int avl_max(int a, int b);

enum Balanceo {
    DESBALANCEADO_DERECHA,
    APENAS_DESBALANCEADO_DERECHA,
    BALANCEADO,
    APENAS_DESBALANCEADO_IZQUIERDA,
    DESBALANCEADO_IZQUIERDA
};


ArbolAVL avl_crear() {
    ArbolAVL nuevo_arbol = (ArbolAVL) malloc(sizeof(struct ArbolAVLRep));
    nuevo_arbol->raiz = NULL;
    nuevo_arbol->cantidad_elementos = 0;
    return nuevo_arbol;
}


bool avl_es_vacio(ArbolAVL a) {
    return a->raiz == NULL;
}


bool avl_es_lleno(ArbolAVL a){
    return (a->cantidad_elementos == TAMANIO_MAXIMO);
}


bool avl_es_rama_nula(NodoArbol pa) {
    return pa == NULL;
}


int avl_cantidad_elementos(ArbolAVL a) {
    return a->cantidad_elementos;
}


NodoArbol avl_raiz(ArbolAVL a) {
    return a->raiz;
}


/*
NodoArbol avl_crear_nodo(TipoElemento te) {
    NodoArbol na = (NodoArbol) malloc(sizeof(struct NodoArbolRep));
    na->datos = te;
    na->hi = NULL;
    na->hd = NULL;
    na->FE = 0;
    return na;
}
*/

enum Balanceo avl_calcular_balanceo(NodoArbol nodo) {
    int diferenciaAltura = avl_altura_izq(nodo) - avl_altura_der(nodo);
    switch (diferenciaAltura) {
        case -2:
            return DESBALANCEADO_DERECHA;
        case -1:
            return APENAS_DESBALANCEADO_DERECHA;
        case 1:
            return APENAS_DESBALANCEADO_IZQUIERDA;
        case 2:
            return DESBALANCEADO_IZQUIERDA;
        default:
            return BALANCEADO;
    }
}


NodoArbol avl_insertar_recursivo(ArbolAVL a, TipoElemento te, NodoArbol pa, bool *inserto) {
    if (pa == NULL) {
        *inserto =true;
        return n_crear(te);
    }

    if (te->clave < pa->datos->clave) {
        pa->hi = avl_insertar_recursivo(a, te, pa->hi, inserto);
    } else if (te->clave > pa->datos->clave) {
        pa->hd = avl_insertar_recursivo(a, te, pa->hd, inserto);
    } else {
        // Es una inserción de un elemento duplicado
        // decrementamos para compensar el incremento
        // hecho anteriormente
        a->cantidad_elementos--;
        return pa;
    }

    pa->FE = avl_max(avl_altura_izq(pa), avl_altura_der(pa)) + 1;
    enum Balanceo balanceState = avl_calcular_balanceo(pa);

    if (balanceState == DESBALANCEADO_IZQUIERDA) {
        if (te->clave < pa->hi->datos->clave) {
            // Caso rotación derecha
            pa = avl_rotar_derecha(pa);
        } else {
            // Caso rotación izquierda-derecha
            pa->hi = avl_rotar_izquierda(pa->hi);
            return avl_rotar_derecha(pa);
        }
    }

    if (balanceState == DESBALANCEADO_DERECHA) {
        if (te->clave > pa->hd->datos->clave) {
            // Caso rotación izquierda
            pa = avl_rotar_izquierda(pa);
        } else {
            // Caso rotación derecha-izquierda
            pa->hd = avl_rotar_derecha(pa->hd);
            return avl_rotar_izquierda(pa);
        }
    }

    return pa;
}

bool avl_insertar(ArbolAVL a, TipoElemento te) {
    bool inserto = false;
    a->raiz = avl_insertar_recursivo(a, te, avl_raiz(a), &inserto);
    a->cantidad_elementos++;
    return inserto;
}


NodoArbol avl_buscar_minimo(NodoArbol nodoArbol) {
    NodoArbol actual = nodoArbol;

    while (actual && actual->hi != NULL)
        actual = actual->hi;

    return actual;
}


NodoArbol avl_eliminar_recursivo(ArbolAVL arbol, NodoArbol nodoArbol, int claveABorrar, bool *borre) {
    if (nodoArbol == NULL) {
        arbol->cantidad_elementos++; // No lo encontramos, sumamos para compensar
        return nodoArbol;
    }

    if (claveABorrar < nodoArbol->datos->clave)
        nodoArbol->hi = avl_eliminar_recursivo(arbol, nodoArbol->hi, claveABorrar, borre);
    else if (claveABorrar > nodoArbol->datos->clave)
        nodoArbol->hd = avl_eliminar_recursivo(arbol, nodoArbol->hd, claveABorrar, borre);
    else {
        // encontre la clave
        *borre = true;
	// es una hoja
        if (nodoArbol->hi == NULL && nodoArbol->hd == NULL) {
//          free(nodoArbol);
            nodoArbol = NULL;
        } else if (nodoArbol->hi == NULL && nodoArbol->hd != NULL) {
	      // Un solo hijo x derecha
              nodoArbol = nodoArbol->hd;
//            NodoArbol temp = nodoArbol->hd;
//            free(nodoArbol);
//            return temp;
        } else if (nodoArbol->hi != NULL && nodoArbol->hd == NULL) {
              // Un solo hijo x izquierda
	      nodoArbol = nodoArbol->hi;
//            NodoArbol temp = nodoArbol->hi;
//            free(nodoArbol);
//            return temp;
        } else {
            // El nodo tiene 2 hijos, buscamos el sucesor en in-orden (o sea el menor del subárbol de la derecha)
            NodoArbol temp = avl_buscar_minimo(nodoArbol->hd);
            nodoArbol->datos->clave = temp->datos->clave;
            nodoArbol->datos->valor = temp->datos->valor;
            nodoArbol->hd = avl_eliminar_recursivo(arbol, nodoArbol->hd, temp->datos->clave, borre);
        }
    }

    if (nodoArbol == NULL) {
        return nodoArbol;
    }

    // Actualizar altura y re-balancear el árbol de ser necesario
    nodoArbol->FE = avl_max(avl_altura_izq(nodoArbol), avl_altura_der(nodoArbol)) + 1;
    enum Balanceo balanceState = avl_calcular_balanceo(nodoArbol);

    if (balanceState == DESBALANCEADO_IZQUIERDA) {
        if (avl_calcular_balanceo(nodoArbol->hi) == BALANCEADO ||
                avl_calcular_balanceo(nodoArbol->hi) == APENAS_DESBALANCEADO_IZQUIERDA) {
            return avl_rotar_derecha(nodoArbol);
        }

        // avl_calcular_balanceo(nodoArbol->hi) === Balanceo.APENAS_DESBALANCEADO_DERECHA
        nodoArbol->hi = avl_rotar_izquierda(nodoArbol->hi);
        return avl_rotar_derecha(nodoArbol);
    }

    if (balanceState == DESBALANCEADO_DERECHA) {
        if (avl_calcular_balanceo(nodoArbol->hd) == BALANCEADO ||
                avl_calcular_balanceo(nodoArbol->hd) == APENAS_DESBALANCEADO_DERECHA) {
            return avl_rotar_izquierda(nodoArbol);
        }
        // avl_calcular_balanceo(nodoArbol->hd) === Balanceo.APENAS_DESBALANCEADO_DERECHA
        nodoArbol->hd = avl_rotar_derecha(nodoArbol->hd);
        return avl_rotar_izquierda(nodoArbol);
    }

    return nodoArbol;
}

bool avl_eliminar(ArbolAVL a, int claveABorrar) {
    bool borre = false;
    a->raiz = avl_eliminar_recursivo(a, avl_raiz(a), claveABorrar, &borre);
    a->cantidad_elementos--;
    return borre;
}


TipoElemento avl_buscar_recursivo(NodoArbol nodoArbol, int clave) {
    if (nodoArbol == NULL)
        return NULL;
    else if (clave < nodoArbol->datos->clave)
        return avl_buscar_recursivo(nodoArbol->hi, clave);
    else if (clave > nodoArbol->datos->clave)
        return avl_buscar_recursivo(nodoArbol->hd, clave);
    else
        return nodoArbol->datos;
}

TipoElemento avl_buscar(ArbolAVL a, int clave) {
    return avl_buscar_recursivo(avl_raiz(a), clave);
}


////////////////////////////////////
///  Funciones para el balanceo  ///
////////////////////////////////////

int avl_altura_izq(NodoArbol nodo) {
    if (nodo->hi == NULL) {
        return -1;
    }
    return nodo->hi->FE;
}

int avl_altura_der(NodoArbol nodo) {
    if (nodo->hd == NULL) {
        return -1;
    }
    return nodo->hd->FE;
}

int avl_max(int a, int b) {
    return a > b ? a : b;
}

/**
 *  * Rotación izquierda
 *   a                                     b
 *  / \                                   / \
 * c   b  -> a.avl_rotar_izquierda() ->  a   e
 *    / \                               / \
 *   d   e                             c   d
 */
NodoArbol avl_rotar_izquierda(NodoArbol nodo) {
    NodoArbol otro = nodo->hd;
    nodo->hd = otro->hi;
    otro->hi = nodo;
    nodo->FE = avl_max(avl_altura_izq(nodo), avl_altura_der(nodo)) + 1;
    otro->FE = avl_max(avl_altura_der(otro), nodo->FE) + 1;

    return otro;
}

/**
 * Rotación derecha
 *     b                                 a
 *    / \                               / \
 *   a   e -> b.avl_rotar_derecha() -> c   b
 *  / \                                   / \
 * c   d                                 d   e
 */
NodoArbol avl_rotar_derecha(NodoArbol nodo) {
    NodoArbol otro = nodo->hi;
    nodo->hi = otro->hd;
    otro->hd = nodo;
    nodo->FE = avl_max(avl_altura_izq(nodo), avl_altura_der(nodo)) + 1;
    otro->FE = avl_max(avl_altura_izq(otro), nodo->FE) + 1;

    return otro;
}

#include "arbol-binario-busqueda.h"
#include "nodo.h"

static const int TAMANIO_MAXIMO = 100;


struct ArbolBinarioBusquedaRep {
    NodoArbol raiz;
    int cantidad_elementos;
};


ArbolBinarioBusqueda abb_crear() {
    ArbolBinarioBusqueda nuevo_arbol = (ArbolBinarioBusqueda) malloc(sizeof(struct ArbolBinarioBusquedaRep));
    nuevo_arbol->raiz = NULL;
    nuevo_arbol->cantidad_elementos = 0;
    return nuevo_arbol;
}


bool abb_es_vacio(ArbolBinarioBusqueda a) {
    return (a->raiz == NULL);
}


bool abb_es_lleno(ArbolBinarioBusqueda a){
    return (a->cantidad_elementos == TAMANIO_MAXIMO);

};


int abb_cantidad_elementos(ArbolBinarioBusqueda a) {
    return a->cantidad_elementos;
}


bool abb_es_rama_nula(NodoArbol pa) {
    return pa == NULL;
}


NodoArbol abb_raiz(ArbolBinarioBusqueda a) {
    return a->raiz;
}



NodoArbol abb_insertar_recursivo(ArbolBinarioBusqueda a, NodoArbol pa, TipoElemento te, bool *inserto) {
    if (pa == NULL) {
	*inserto = true;
        a->cantidad_elementos++;
        NodoArbol nuevo_nodo = n_crear(te);
        if (a->cantidad_elementos == 1) {
            a->raiz = nuevo_nodo;
        }
        return nuevo_nodo;
    } else if (te->clave > pa->datos->clave) {
        pa->hd = abb_insertar_recursivo(a, pa->hd, te, inserto);
    } else if (te->clave < pa->datos->clave) {
        pa->hi = abb_insertar_recursivo(a, pa->hi, te, inserto);
    }
    return pa;
}

bool abb_insertar(ArbolBinarioBusqueda a, TipoElemento te) {
    bool inserto = false;
    if (abb_es_vacio(a)) {
        a->raiz = n_crear(te);
        a->cantidad_elementos++;
	inserto = true;
    } else {
        NodoArbol p, q;
        q = abb_raiz(a);
        while (q != NULL) {
            p = q;
            if (te->clave < q->datos->clave) {
                q = q->hi;
            } else if (te->clave > q->datos->clave) {
                q = q->hd;
            } else {
                break;
            }
        }
        if (q == NULL) {
            inserto = true;
            NodoArbol na = n_crear(te);
            a->cantidad_elementos++;
            if (p->datos->clave > te->clave) {
                p->hi = na;
            } else {
                p->hd = na;
            }
        } else {
            printf("Clave Duplicada: %d \n", te->clave);
        }
    }
    return inserto;
//    abb_insertar_recursivo(a, abb_raiz(a), te, &inserto);
}


NodoArbol abb_buscar_minimo(NodoArbol nodoArbol) {
    NodoArbol actual = nodoArbol;

    while (actual && actual->hi != NULL)
        actual = actual->hi;

    return actual;
}

NodoArbol abb_eliminar_recursivo(NodoArbol root, int claveABorrar, bool *borre) {
    if (root == NULL) {
        return root;
    }

    if (claveABorrar < root->datos->clave)
        root->hi = abb_eliminar_recursivo(root->hi, claveABorrar, borre);
    else if (claveABorrar > root->datos->clave)
        root->hd = abb_eliminar_recursivo(root->hd, claveABorrar, borre);
    else {
        borre = true;
        if (root->hi == NULL) {
            NodoArbol temp = root->hd;
            free(root);
            return temp;
        } else if (root->hd == NULL) {
            NodoArbol temp = root->hi;
            free(root);
            return temp;
        }

        NodoArbol temp = abb_buscar_minimo(root->hd);
        root->datos->clave = temp->datos->clave;
        root->datos->valor = temp->datos->valor;

        root->hd = abb_eliminar_recursivo(root->hd, temp->datos->clave, borre);
    }
    return root;
}


bool abb_eliminar(ArbolBinarioBusqueda a, int claveABorrar) {
    bool borre = false;
    TipoElemento te;
    NodoArbol N;
    te = n_recuperar(abb_raiz(a));

    // cotemplo que si borra la raiz y no tiene hijos por la derecha el hijo izquierdo se convierte en raiz
    N = n_hijoderecho(abb_raiz(a));
    if ((N == NULL) && (te->clave == claveABorrar)) {
        printf("Hijo Derecho NULO \n");
        N = abb_raiz(a);
        a->raiz = n_hijoizquierdo(abb_raiz(a));
        free(N);
        return true;
    }

    // cotemplo que si borra la raiz y no tiene hijos por la izquierda el hijo derecho se convierte en raiz
    N = n_hijoizquierdo(abb_raiz(a));
    if ((N == NULL) && (te->clave == claveABorrar)) {
        printf("Hijo Izquierdo NULO \n");
        N = abb_raiz(a);
        a->raiz = n_hijoderecho(abb_raiz(a));
        free(N);
        return true;
    }

    // Cualquier otro caso
    // Sino llamo al proceso recursivo
    abb_eliminar_recursivo(abb_raiz(a), claveABorrar, &borre);
    return borre;
}


TipoElemento abb_buscar_recursivo(NodoArbol nodoArbol, int clave) {
    if (nodoArbol == NULL)
        return NULL;
    else if (clave < nodoArbol->datos->clave)
        return abb_buscar_recursivo(nodoArbol->hi, clave);
    else if (clave > nodoArbol->datos->clave)
        return abb_buscar_recursivo(nodoArbol->hd, clave);
    else
        return nodoArbol->datos;

}

TipoElemento abb_buscar(ArbolBinarioBusqueda a, int clave) {
    return abb_buscar_recursivo(abb_raiz(a), clave);
}


#include <stdlib.h>
#include <string.h>
#include "arbol-binario.h"
#include "colas.h"
#include "nodo.h"

static const int TAMANIO_MAXIMO = 100;


struct ArbolBinarioRep {
    NodoArbol raiz;
    int cantidad_elementos;
};


ArbolBinario a_crear() {
    ArbolBinario nuevo_arbol = (ArbolBinario) malloc(sizeof(struct ArbolBinarioRep));
    nuevo_arbol->raiz = NULL;
    nuevo_arbol->cantidad_elementos = 0;
    return nuevo_arbol;
}

bool a_es_vacio(ArbolBinario a) {
    return a->raiz == NULL;
}

bool a_es_lleno(ArbolBinario a){
    return (a->cantidad_elementos == TAMANIO_MAXIMO);
}

int a_cantidad_elementos(ArbolBinario a) {
    return a->cantidad_elementos;
}

bool a_es_rama_nula(NodoArbol pa) {
    return pa == NULL;
}

NodoArbol a_raiz(ArbolBinario a) {
    return a->raiz;
}

NodoArbol a_establecer_raiz(ArbolBinario a, TipoElemento te) {
    if (a->raiz != NULL) {
        // TODO Acá debería ser un error
        // No se puede l_insertar la raíz de un árbol que ya tiene raíz
        return a->raiz;
    }

    NodoArbol na = n_crear(te);
    a->raiz = na;
    a->cantidad_elementos++;
    return na;
}

NodoArbol a_conectar_hi(ArbolBinario a, NodoArbol pa, TipoElemento te) {
    // TODO Acá deberíamos chequear que la posición árbol efectivamente esté en el árbol
    if (pa == NULL) {
        return NULL;
    }

    // Chequeamos que la posición árbol no tenga ya la rama que están solicitando l_insertar
    if (pa->hi != NULL) {
        // TODO Deberíamos devolver error
        return pa->hi;
    }

    NodoArbol na = n_crear(te);
    a->cantidad_elementos++;

    pa->hi = na;

    return na;
}

NodoArbol a_conectar_hd(ArbolBinario a, NodoArbol pa, TipoElemento te) {
    // TODO Acá deberíamos chequear que la posición árbol efectivamente esté en el árbol
    if (pa == NULL) {
        return NULL;
    }

    // Chequeamos que la posición árbol no tenga ya la rama que están solicitando l_insertar
    if (pa->hd != NULL) {
        // TODO Deberíamos devolver error
        return pa->hd;
    }

    NodoArbol na = n_crear(te);
    a->cantidad_elementos++;

    pa->hd = na;

    return na;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodo.h"

// retorna el hijo izquierdo
NodoArbol n_hijoizquierdo(NodoArbol N){
    if (N == NULL) {
        return NULL;
    }
    else {
        return N->hi;
    }
};

// retorna el hijo derecho
NodoArbol n_hijoderecho(NodoArbol N){
    if (N == NULL) {
        return NULL;
    }
    else {
        return N->hd;
    }
};

// Crea el Nodo y lo retorna
NodoArbol n_crear(TipoElemento te) {
    NodoArbol na = (NodoArbol) malloc(sizeof(struct NodoArbolRep));
    na->datos = te;
    na->hi = NULL;
    na->hd = NULL;
    na->FE = 0;
    return na;
};

// retorno el tipo elemento de un nodo o NULL si no existe
TipoElemento n_recuperar(NodoArbol N) {
    TipoElemento x = te_crear(0);
    if (N == NULL) {
        return NULL;
    }
    else {
        x = N->datos;
        return x;
    }
};



#include "tipo_elemento.h"
#include <stdlib.h>

TipoElemento te_crear(int clave) {
    TipoElemento te = (TipoElemento) malloc(sizeof (struct TipoElementoRep));
    te->clave = clave;
    te->valor = NULL;
    return te;
}

TipoElemento te_crear_con_valor(int clave, void* valor) {
    TipoElemento te = (TipoElemento) malloc(sizeof (struct TipoElementoRep));
    te->clave = clave;
    te->valor = valor;
    return te;
}

#ifndef TP_ARBOLES_H
#define TP_ARBOLES_H

#include <stdbool.h>
#include "colas.h"
#include "listas.h"
#include "pilas.h"
#include "nodo.h"
#include "arbol-binario.h"
#include "arbol-avl.h"
#include "arbol-binario-busqueda.h"


/**
2.	Dado un árbol binario no vacío determinar:  
 */

//  a.	Retornar una lista con todos los nodos terminales u hojas.
Lista a_ej2_hojas(ArbolBinario A);

//  b.	Retornar en una estructura todos los nodos interiores (los que no son ni hojas ni raíz)
Lista a_ej2_interiores(ArbolBinario A);

//  c.	Buscar todas las ocurrencias de una clave dentro del árbol. Retornar la posición de cada ocurrencia (puntero al nodo).
Lista a_ej2_buscarclave(ArbolBinario A, int clave);


/**
3.	Para un nodo del árbol binario determinado:

 */

// a.	Indicar el nombre del nodo padre (clave).
int a_ej3_clavepadre(ArbolBinario A, int clavehijo);

// b.	Listar los hijos (solo las clave/s).
Lista a_ej3_hijos(ArbolBinario A, int clavepadre);

// c.	Listar el hermano (solo la clave).
int a_ej3_hermano(ArbolBinario A, int clave);

// d.	Calcular el nivel en el que se encuentra.
int a_ej3_nivel(ArbolBinario A, int clave);

// e.	Calcular la altura de su rama (Altura del Subárbol)
int a_ej3_alturarama(ArbolBinario A, int clave);

// f.	Listar todos los nodos que están en el mismo nivel (solo la clave).
Lista a_ej3_clavesmismonivel(ArbolBinario A, int nivel);


/**
4.	Para Árboles “N-arios”:
 */
// a.	Dado un árbol n-ario, devolver en forma de lista el resultado del recorrido en anchura del árbol  (solo las claves).
Lista a_ej4_anchura(ArbolBinario A);

// b.	Escribir una función que, dado un árbol n-ario, devuelva el número (cantidad) de hojas de dicho árbol.
int a_ej4_q_hojas(ArbolBinario A);

// c.	Escribir una función booleana que dados dos árboles generales determine si tienen la misma estructura, sin importar los datos del mismo (árbol similar).
bool a_ej4_similares(ArbolBinario A, ArbolBinario B);

// d.	Retornar el padre de un nodo del árbol (tipo_elemento).
TipoElemento a_ej4_padre(ArbolBinario A, int clave);

// e.	Retornar los hermanos de un nodo del árbol (lista de hermanos).
Lista a_ej4_hermanos(ArbolBinario A, int clave);



/**
7.	Determinar si dos árboles binarios son equivalentes.
 */
bool a_ej7_equivalente(ArbolBinario A, ArbolBinario B);


/**
8.	Dado un árbol “n-ario” se pide:
 */
// a.	Determinar la altura del mismo.
int c_ej8_altura(ArbolBinario A);

// b.	Determinar el nivel de un nodo.
int c_ej8_nivel(ArbolBinario A, int clave);

// c.	Listar todos los nodos internos (solo las claves).
Lista c_ej8_internos(ArbolBinario A);

// d.	Determinar si todas las hojas están al mismo nivel.
bool c_ej8_hojasmismonivel(ArbolBinario A);


/**
9.	Generar un algoritmo, recursivo o no, que permita construir un árbol binario de búsqueda balanceado (AVL) 
	a partir de un árbol binario sin un orden determinado.  
	Comparar las alturas de ambos árboles. Determinar la complejidad algorítmica.
 */
// Primero llamamos para construir el AVL
ArbolAVL a_ej9_construiravl(ArbolBinario A);

// Luego con el resultado de la funcion anterior llamamos a una funcion para que nos retorne la diferencia de las alturas 
// comparadas como Altura(ArbolBinario) - Altura(ArbolAVL).
int a_ej9_diferenciaalturas(ArbolBinario A, ArbolAVL AVL);


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


#endif // TP_ARBOLES_H
