#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tabla_hash.h"
#include "listas.h"

struct TipoRegistroTabla {
    TipoElemento tipo_elemento;
    bool ocupado;
    Lista lista_colisiones;
};

struct TablaHashRep {
    int (*hash_function)(int); //puntero a la función hash
    int capacidad;
    struct TipoRegistroTabla *tabla;
};

/*Objetivo: Inicializar la tabla hash creando vacía cada una de las lista de 
colisiones de cada posición. Inicializa el tipo de datos de la clave y cual
es la función Hash a utilizar.*/
TablaHash th_crear(int capacidad, int (*hash_function)(int)) {
    TablaHash nueva_tabla_hash = (TablaHash) malloc(sizeof(struct TablaHashRep));
    nueva_tabla_hash->capacidad = capacidad;
    nueva_tabla_hash->hash_function = hash_function;

    nueva_tabla_hash->tabla = (struct TipoRegistroTabla *) malloc(capacidad * sizeof(struct TipoRegistroTabla));
    for (int i = 0; i < capacidad; ++i) {
        nueva_tabla_hash->tabla[i].tipo_elemento = NULL;
        nueva_tabla_hash->tabla[i].ocupado = false;
        nueva_tabla_hash->tabla[i].lista_colisiones = l_crear();
    }
    return nueva_tabla_hash;
}

/*Objetivo: inserta una clave dentro de la tabla usando la función «hash».
Si nunca fue ocupada esa posición pone la clave y la marca como
ocupada. Si ya fue ocupada entonces:
1. Si una clave esta repetida no la inserta.
2. Si una clave es sinónima también va a la lista de colisiones.*/
bool th_insertar(TablaHash th, TipoElemento te) {
    int pos = th->hash_function(te->clave);
    struct TipoRegistroTabla *registroTabla = &th->tabla[pos];
    if (!registroTabla->ocupado) {
        registroTabla->tipo_elemento = te;
        registroTabla->ocupado = true;
        return true;
    } else {
        if (registroTabla->tipo_elemento->clave != te->clave &&
                l_buscar(registroTabla->lista_colisiones, te->clave) == NULL) {
            return l_agregar(registroTabla->lista_colisiones, te);
        }
    }
    return false;
}

/*Objetivo: elimina una clave dentro de la tabla usando la función «hash».
Si la clave esta en la tabla entonces:
1. Si no hay claves en la lista de colisiones, simplemente marca la
posición como NO ocupada.
2. Si hay clave que colisionan, entonces mueve la primer clave de la lista
de colisiones a la tabla y la elimina de la lista.
3. Si la clave esta en la lista de colisiones, simplemente se elimina.*/
bool th_eliminar(TablaHash th, int clave) {
    int pos = th->hash_function(clave);
    struct TipoRegistroTabla *registroTabla = &th->tabla[pos];
    if (registroTabla->ocupado) {
        if (registroTabla->tipo_elemento->clave == clave) {
            if (!l_es_vacia(registroTabla->lista_colisiones)) {
                registroTabla->tipo_elemento = l_recuperar(registroTabla->lista_colisiones, 1);
                return l_eliminar(registroTabla->lista_colisiones, 1);
            } else {
                registroTabla->ocupado = false;
                registroTabla->tipo_elemento = NULL;
		return true;
            }
        } else {
            return l_borrar(registroTabla->lista_colisiones, clave);
        }
    }
}

/*Objetivo: buscar una clave dentro de la tabla usando la función «hash».
Si la clave existe retorna el tipo elemento.
Si la clave no existe retorna NULL.*/
TipoElemento th_recuperar(TablaHash th, int clave) {
    int pos = th->hash_function(clave);
    struct TipoRegistroTabla *registroTabla = &th->tabla[pos];
    if (registroTabla->ocupado) {
        if (registroTabla->tipo_elemento->clave == clave) {
            return registroTabla->tipo_elemento;
        } else {
            return l_buscar(registroTabla->lista_colisiones, clave);
        }
    }
    return NULL;
}

void th_mostrar_interna(TablaHash th, bool soloOcupados) {
    printf("Contenido de la tabla hash:\n");
    for (int i = 0; i < th->capacidad; i++) {
        struct TipoRegistroTabla registroTabla = th->tabla[i];
        if (registroTabla.ocupado) {
            printf("  tabla[%i] [ocupado] %i", i, registroTabla.tipo_elemento->clave);
            Iterador iter = iterador(registroTabla.lista_colisiones);
            while (hay_siguiente(iter)) {
                TipoElemento e = siguiente(iter);
                printf(" -> %i ", e->clave);
            }
            free(iter);
            printf("\n");
        } else if (!soloOcupados) {
            printf("  tabla[%i] [ libre ]\n", i);
        }
    }
    printf("\n");
}

/*Objetivo: muestra la tabla completa mostrando las posiciones libres y
ocupadas junto a la lista de colisiones en los casos que corresponda.*/
void th_mostrar(TablaHash th) {
    th_mostrar_interna(th, false);
}

/*Objetivo: muestra solo las posiciones de la tabla ocupada junto a la lista
de colisiones en los casos que corresponda.*/
void th_mostrar_solo_ocupados(TablaHash th) {
    th_mostrar_interna(th, true);
}
