#include <stdlib.h>
#include <stdio.h>

#include "./libraries/myString.h"
#include "./libraries/languaje.h"

int main() {

    String *cadena1 = readString();
    String *cadena2 = readString();
    String *cadena3 = readString();
    
/*
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
    
    showString(powString( cadena1, p ));*/

    Languaje *newLang = initLanguaje();

    addString( newLang, cadena1 );
    addString( newLang, cadena2 );
    addString( newLang, cadena2 );

    printf("Lenguaje 1: \n");

    showLanguaje( newLang );

    printf("\n");

    Languaje *nL2 = initLanguaje();

    addString( nL2, cadena3 );
    addString( nL2, cadena2 );
    addString( nL2, cadena1 );

    printf("Lenguaje 2: \n");

    showLanguaje( nL2 );

    printf("\n");

    Languaje *lc = languajeUnion( newLang, nL2 );

    printf("Lenguaje Unificado: \n");

    showLanguaje( lc );

    printf("\n");

    Languaje *ld = languajeConcat( newLang, nL2 );

    printf("Lenguaje concatenado: \n");

    showLanguaje( ld );

    printf("\n");

    Languaje *li = invertLanguaje( newLang );

    printf("Lenguaje invertido: \n");

    showLanguaje( li );

    printf("\n");

    return 0;
}