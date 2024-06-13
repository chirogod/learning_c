#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TP1_Recursividad.h"
// Ejercicio 1
/*1.	Construir una función recursiva que retorne verdadero si una cadena de caracteres pasada 
como parámetro es un palíndromo.  Ej. “neuquen” ya que se lee igual de atrás hacia adelante.*/
bool palindormo (char *palabra, int inicio, int fin){
    if(inicio >= fin){ //osea que 0 >= a strlen(palabra) que si es 0 no tiene nada la palabra
        return true;
    }
    if (palabra[inicio] != palabra[fin])//si la posicion 0 de la palabra es diferente a la ultima posicion retorna falso
    {
        return false;
    }
    return palindormo(palabra, inicio+1, fin-1);//retornar la funcion pasandole la siguiente posicion de inicio y la anterior de la ultima
    
}

int main(){
    char palabra[] = "aaawa";
    if (palindormo(palabra, 0, strlen(palabra)-1))
    {
        printf("Es una palindromo la palabra");
    }else printf("No es un palindromo la palabra");

    return 0;
}
