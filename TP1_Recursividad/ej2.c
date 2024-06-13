#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TP1_Recursividad.h"

// Ejercicio 2
/*2.	Dados dos números enteros m y n, construir una función recursiva que devuelva 
el producto de ambos, calculando el mismo como sumas sucesivas. Esto es: m*n=m+m+...+m, n veces. */

int producto (int m, int n){
    if (n==1){
        return m;
    }
    
    return producto(m+m, n-1);


    
}

int main(){
    int m = 5;
    int n = 5;
    printf("resultado = %d", producto(m,n));
    return 0;
}
