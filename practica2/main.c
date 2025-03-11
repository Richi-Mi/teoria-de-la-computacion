#include <stdlib.h>
#include <stdio.h>

#include "myString.h"

int main() {

    String *cadena1 = readString();
    String *cadena2 = readString();
    

    printf("Cadena 1: ");
    showString( cadena1 );

    printf("Cadena 2: ");
    showString( cadena2 );

    printf("La cadena concatenada es: ");
    showString( concat( cadena1, cadena2 ) );

    printf("La cadena 1 invertida es: ");
    showString( inverseString( cadena1 ) );

    int p;
    printf("Ingrese el valor de p: ");
    scanf("%d", &p);
    
    showString(powString( *cadena1, p ));

    return 0;
}