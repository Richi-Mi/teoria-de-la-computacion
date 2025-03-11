#include <stdlib.h>
#include <stdio.h>

#include "./libraries/myString.h"
#include "./libraries/languaje.h"
// Cerradura de Kleane (Calcular hasta la 4ta potencia)
Languaje* cerraduraDeKleene( Languaje *lang ) {
    Languaje *la = initLanguaje();
    
    for( int i = 1; i <= 4; i++ ) {
        Languaje *aux = powLanguaje( lang, i );
        la = languajeUnion( la, aux );
    }
    addString( la, cadenaVacia() );
    return la;
}
Languaje* cerraduraPositiva( Languaje *lang ) {
    Languaje *la = initLanguaje();
    for( int i = 1; i <= 4; i++ ) {
        Languaje *aux = powLanguaje( lang, i );
        la = languajeUnion( la, aux );
    }
    return la;
}

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
    addString( newLang, cadena3 );

    //printf("Lenguaje 1: \n");

    //showLanguaje( newLang );

    //printf("\n");

    Languaje *nL2 = initLanguaje();

    addString( nL2, cadena3 );
    addString( nL2, cadena2 );
    addString( nL2, cadena1 );

    Languaje *k = cerraduraPositiva( newLang );
    showLanguaje( k );


    printf("\n");

    return 0;
}