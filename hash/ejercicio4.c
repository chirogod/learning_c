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
#define TAMANO_HASH 100

typedef struct {
    int legajo;
    char apellido[20];
    char nombre[20];
    char domicilio[50];
} Alumno;



int hashFunction(int clave){
    return clave % TAMANO_HASH;
}

void cargarTablaDesdeArchivo(TablaHash th) {
    FILE *falum;
    Alumno alumno;

    falum = fopen("alumnos.txt", "r");
    if (falum == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    while (fscanf(falum, "%d %s %s %s \n]", alumno.legajo, alumno.apellido, alumno.nombre, alumno.domicilio) == 4)
    {
        th_insertar(th, alumno.legajo); // Pass the address of the alumno struct
    }

    fclose(falum);
}

int main() {
    TablaHash th = th_crear(TAMANO_HASH, hashFunction);
    cargarTablaDesdeArchivo(th);
    return 0;
}








/*


void cargarAlumno() {
    FILE *falum;
    Alumno alumno;

    falum = fopen("alumnos.txt", "a+");
    if (falum == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    printf("Legajo del alumno: ");
    scanf("%d", &alumno.legajo);
    printf("Nombre del alumno: ");
    scanf("%s", alumno.nombre);
    printf("Apellido del alumno: ");
    scanf("%s", alumno.apellido);
    printf("Domicilio del alumno: ");
    scanf("%s", alumno.domicilio);

    fprintf(falum, "%d %s %s %s %s\n", alumno.legajo, alumno.apellido, alumno.nombre, alumno.domicilio);
    
    fclose(falum);
}

int main() {
    int operacion = 0;

    /*while (operacion != -1) {
        printf("MENU\n");
        printf("Opcion 1: agregar alumno \n");
        printf("Opcion 2: modificar alumno \n");
        printf("Opcion 3: eliminar alumno \n");
        printf("Opcion -1: salir \n");
        printf("Ingrese una opción: ");
        scanf("%d", &operacion);

        switch (operacion) {
            case 1:
                cargarAlumno();
                break;
            case 2:
                // Función para modificar alumno
                break;
            case 3:
                // Función para eliminar alumno
                break;
            case -1:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    }

    return 0;
}*/