/*Desarrollar un algoritmo que dado un archivo que contendrá los datos de alumnos
(legajo, apellido, nombres, domicilio, TE) genere una tabla hash donde la clave será el
legajo y se guardará como dato la posición física del registro para realizar accesos
directos. Hacer un ABM para poder cargar manualmente el archivo. El “legajo" es un
valor de 6 dígitos.
// max de alumnos 100, pero que se pueda cargar menos tmb
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla_hash.h"

#define MAX_LEGAJO_DIGITOS 6
#define NOMBRE_ARCHIVO "alumnos.txt"
#define TAMANIO_HASH 100
