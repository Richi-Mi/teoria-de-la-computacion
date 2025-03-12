#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
// Cerradura positiva.
Languaje* cerraduraPositiva( Languaje *lang ) {
    Languaje *la = initLanguaje();
    for( int i = 1; i <= 4; i++ ) {
        Languaje *aux = powLanguaje( lang, i );
        la = languajeUnion( la, aux );
    }
    return la;
}
void menu() {
    printf("* -------------------------------------------------------------- * \n");
    printf("1. Unión \n");
    printf("2. Concatenación \n");
    printf("3. Potencia (El rango de las potencias posibles será de -5 a 10) \n");
    printf("4. Cerradura Positiva (Calcular hasta la 4ta potencia) \n");
    printf("5. Cerradura de Kleane (Calcular hasta la 4ta potencia) \n");
    printf("6. Reflexión de un lenguaje (Potencia= -1) \n");
    printf("7. Mostrar lenguajes \n");
    printf("* -------------------------------------------------------------- * \n");
}
int main() {

    int index = 0;
    char indexLetter = 49;
    Languaje *arrregloLenguajes[ 50 ];

    Languaje *l1 = readFileAndGetLanguaje("./build/lenguaje1.txt");
    Languaje *l2 = readFileAndGetLanguaje("./build/lenguaje2.txt");
    Languaje *l3 = readFileAndGetLanguaje("./build/lenguaje3.txt");

    arrregloLenguajes[ index ] = l1; 
    index++;
    arrregloLenguajes[ index ] = l2;
    index++;
    arrregloLenguajes[ index ] = l3;
    index++;

    int option; 
    
    do {
        menu();

        printf("Ingresa la opción que deseas realizar: ");
        scanf("%d", &option );

        if( option == 1 ) {
            printf("Ingresa los lenguajes a operar: ");
            int li1, li2;
            scanf("%d,%d", &li1, &li2 );
            
            Languaje *L1 = arrregloLenguajes[ li1 ];
            Languaje *L2 = arrregloLenguajes[ li2 ];

            Languaje *newLang = languajeUnion( L1, L2 );

            arrregloLenguajes[ index ] = newLang;
            index++;

            saveLanguaje( getFileName("union", index ), newLang );
            printf("Lenguaje guardado en: %s\n", "langUnion12.txt" );
        }
        if( option == 2 ) {
            printf("Ingresa los lenguajes a operar: ");
            int li1, li2;
            scanf("%d,%d", &li1, &li2 );

            Languaje *L1 = arrregloLenguajes[ li1 ];
            Languaje *L2 = arrregloLenguajes[ li2 ];

            Languaje *newLang = languajeConcat( L1, L2 );
            arrregloLenguajes[ index ] = newLang;
            index++;

            saveLanguaje( getFileName("concat", index ), newLang );
            printf("Lenguaje guardado en: %s\n", getFileName("concat", index ) );
        }
        if( option == 3 ) {
            printf("Ingresa el lenguaje a operar y la potencia a operar (lang,p): ");
            int li, p;
            scanf("%d,%d", &li, &p );

            Languaje *L = arrregloLenguajes[ li ];
            Languaje *Lpow = powLanguaje( L, p );
            arrregloLenguajes[ index ] = Lpow;
            index++;

            showLanguaje( Lpow );

            saveLanguaje( getFileName("pow", index ), Lpow );
            printf("Lenguaje guardado en: %s\n", getFileName("pow", index ) );
            // TODO: Checar potencias negativas.
        }
        if( option == 4 ) {
            printf("Ingresa el lenguaje a operar: \n");
            int lopt;
            scanf("%d", &lopt);

            Languaje *langCP = cerraduraPositiva( arrregloLenguajes[ lopt ] );
            arrregloLenguajes[ index ] = langCP;
            index++;

            char *fn = getFileName("cerraduraPositiva", index );
            saveLanguaje( fn, langCP );
            printf("Lenguaje guardado en: %s\n", fn );
        }
        if( option == 5 ) {
            printf("Ingresa el lenguaje a operar: \n");
            int lopt;
            scanf("%d", &lopt);

            Languaje *langCP = cerraduraDeKleene( arrregloLenguajes[ lopt ] );
            arrregloLenguajes[ index ] = langCP;
            index++;

            char *fn = getFileName("cerraduraDeKleene", index );
            saveLanguaje( fn, langCP );
            printf("Lenguaje guardado en: %s\n", fn );
        }
        if( option == 6 ) {
            printf("Ingresa el lenguaje a operar: \n");
            int lopt;
            scanf("%d", &lopt);

            Languaje *LI = invertLanguaje( arrregloLenguajes[ lopt ] );
            arrregloLenguajes[ index ] = LI;
            index++;

            char *fn = getFileName("reflexion", index );
            saveLanguaje( fn, LI );
            printf("Lenguaje guardado en: %s\n", fn );
        }
        if( option == 7 ) {
            for( int i = 0; i < index; i++ ) {
                printf("L%d = ", i );
                showLanguaje( arrregloLenguajes[i] );
            }
        }
    } while( option != 0 );
    return 0;
}