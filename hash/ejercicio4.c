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

void guardarLegajoABM(TablaHash th){

    FILE *archivo;
    archivo=fopen("alumnos.txt","r");

    //Leemos los registros
    int legajo, te;
    char nom[20], dom[20];

    while(!(feof(archivo))){
        fscanf(archivo,"%d %s %s %d",&legajo,&nom,&dom,&te);
        TipoElemento e=te_crear(legajo);
        th_insertar(th,e); //INSERTAMOS EL LEGAJO COMO CLAVE EN LA TABLA HASH
        }

    fclose(archivo); 

}
/*
void ABM_Alumnos(){

    FILE *archivo;
    archivo=fopen("alumnos.txt","a");

    //Escribimos el archivo
    int legajo, te;
    char nom[20], dom[20];

    printf("Ingrese el LEGAJO del alumno: ");
    scanf("%d",&legajo);
    printf("Ingrese el APELLIDO,NOMBRE del alumno: ");
    scanf("%s",&nom);
    printf("Ingrese el DOMICILIO del alumno: ");
    scanf("%s",&dom);
    printf("Ingrese el TELEFONO del alumno: ");
    scanf("%d",&te);

    fprintf(archivo,"%d %s %s %d\n",legajo,nom,dom,te); //imprimir datos al final del archivo

    fclose(archivo); 

}
*/
//FUNCIÓN HASH
int hashfunction(int clave){
    return clave%TAMANO_HASH;
}


int main() {
    TablaHash th = th_crear(TAMANO_HASH, &hashfunction);

    // Cargar datos desde el archivo y guardarlos en la tabla hash
    guardarLegajoABM(th);

    // Mostrar los datos de la tabla hash
    th_mostrar(th);

    return 0;
}