#include <stdlib.h>
#include <stdio.h>

#include "./libraries/myString.h"
#include "./libraries/languaje.h"
#include "./libraries/archivos.h"

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

    Languaje *l1 = readFileAndGetLanguaje("./build/lenguaje1.txt");
    Languaje *l2 = readFileAndGetLanguaje("./build/lenguaje2.txt");
    Languaje *l3 = readFileAndGetLanguaje("./build/lenguaje3.txt");

    Languaje *l4 = cerraduraPositiva( l1 );

    saveLanguaje("./build/l4.txt", l4 );

    return 0;
}