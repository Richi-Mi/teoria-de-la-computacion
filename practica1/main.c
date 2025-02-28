#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "listas.h"


#define MAX 50

int readString( char *cadena );
void inverseString( Nodo *cadena, char *result );
void showMenu();

void concat( List *lista );
void strPow( List *lista );
void inverse( List *lista ); 
void prefijos( List *lista );
void sufijos( List *lista );
void subcadenas( List *lista );

int main() {
    char palabra1[MAX];
    char palabra2[MAX];
    
    // Lectura de cadenas.
    printf("Ingrese la cadena x: ");
    int l1 = readString( palabra1 );
    printf("Ingrese la cadena y: ");
    int l2 = readString( palabra2 );

    // Inicializar la lista.
    List listaCadenas;
    listaCadenas.inicial = NULL;
    listaCadenas.lenght  = 0;

    addElement( &listaCadenas, palabra1, l1 );
    addElement( &listaCadenas, palabra2, l2 );

    int option = 0;

    do {
        showMenu();

        scanf("%d", &option );

        switch( option ) {
            case 1:
                concat( &listaCadenas );
            break;

            case 2:
                prefijos( &listaCadenas );
            break;

            case 3:
                sufijos( &listaCadenas );
            break;

            case 4:
                inverse( &listaCadenas );
            break;

            case 5:
                strPow( &listaCadenas );
            break;

            case 6:
                showElements( listaCadenas );
            break;

            case 7:
                subcadenas( &listaCadenas );
            break;

            default:
                option = 0;
            break;
        }
    } while( option != 0 );

    eraseList( &listaCadenas );
}
int readString( char* cadena ) {
    int i = 0;
    char c;
    while( ( c = getchar() ) != '\n') {
        if( !(i >= MAX) ) {
            cadena[i] = c;
            i++;
        }
        else {
            return -1;
        }
    }
    return i;
}
// Función para mostrar el menú
void showMenu() {
    printf("\n*--------------------------------*\n");
    printf("1. Concatenación de las cadenas \n");
    printf("2. Prefijos de una cadena       \n");
    printf("3. Sufijos de una cadena        \n");
    printf("4. Inversión de una cadena      \n");
    printf("5. Potencia de una cadena       \n");
    printf("6. Ver cadenas                  \n");
    printf("7. Obtener todas las subcadenas \n");
    printf("0. Salir                        ");
    printf("\n*--------------------------------*\n");
}
// Operaciones con cadenas.
void concat( List *lista ) {
    printf("Escoje el indice de las cadenas que vas a concatenar: \nFormato: (indice1, indice2)\n");
    int i1, i2; 
    scanf("%d,%d", &i1, &i2);

    Nodo *cad1 = getString( lista, i1 );
    Nodo *cad2 = getString( lista, i2 );

    int newLenght = cad1->lenght + cad2->lenght + 1; // Para '\0'
    char *newCad = (char *) malloc( newLenght * sizeof( char ) );    

    // Función de la libreria strings.h que concatena 2 cadenas.
    strcat( newCad, cad1->cadena );
    strcat( newCad, cad2->cadena );

    addElement( lista, newCad, newLenght );

    printf("Cadena agregada: 🥵 %s\n", newCad );
}
void strPow( List *lista ) {
    printf("Ingrese el indice de la cadena, y el indice a elevarla: \nFormato: (iCad, iPow)\n");
    int iCad, iPow, i;
    scanf("%d,%d", &iCad, &iPow);

    Nodo *cad = getString( lista, iCad );

    if( iPow == 0 ) {
        char *newCad = "";
        addElement( lista, newCad, 0 );
    }
    int lenght = (cad->lenght * iPow) + 1;
    if( iPow > 0 ) {
        char *newCad = (char *) malloc( lenght * sizeof(char) );
        for( i = 0; i < iPow; i++ )
            strcat( newCad, cad -> cadena);
        
        addElement( lista, newCad, lenght );
    }
    if( iPow < 0 ) {
        char *newCad = (char *) malloc( ( lenght * (-1)) * sizeof(char));
        char *invCad = (char *) malloc( cad->lenght * sizeof(char) );

        inverseString( cad, invCad );

        for( i = iPow; i <= 0; i++ )
            strcat( newCad, invCad);

        addElement( lista, newCad, lenght );
    }
    printf("Cadena agregada 😎");
}
void inverseString( Nodo *cadena, char *result ) {
    int i, j = 0;
    
    for( i = cadena->lenght - 1; i >= 0; i-- ) {
        result[i] = cadena->cadena[j];
        j++;
    }
}
void inverse( List *lista ) {
    
    printf("Ingrese el indice de la cadena a invertir: ");
    int opt;
    scanf("%d", &opt );

    Nodo *string = getString( lista, opt );

    char *inverseCad = malloc( string->lenght * sizeof(char) );
    inverseString( string, inverseCad );

    printf("Cadena invertida: %s", inverseCad );
}
void prefijos( List *lista ) {
    int index, i, j;
    printf("Ingresa el indice de la cadena a procesar: ");
    scanf("%d", &index);

    Nodo *string = getString( lista, index );
    for( i = 0; i <= string->lenght; i++ ) {
        printf("🤩 ");
        for( j = 0; j < i; j++ ) {
            printf("%c", string->cadena[j]);
        }
        printf("\n");
    }

}
void sufijos( List *lista ){
    int index, i, j;
    printf("Ingresa el indice de la cadena a procesar: ");
    scanf("%d", &index);

    Nodo *string = getString( lista, index );

    for( i = string->lenght; i >= 0; i-- ) {
        printf("💀 ");
        for( j = 0; j <= string->lenght; j++ ) {
            if( j < i ) 
                printf(" ");
            else 
                printf("%c", string->cadena[j]);
        }
        printf("\n");
    }
}
void subcadenas( List *lista ) {
    int index;
    printf("Ingresa el indice de la cadena a procesar: ");
    scanf("%d", &index);

    Nodo *string = getString( lista, index );

    for( int i = 0; i <= string->lenght; i++ ) {
        for( int j = i; j <= string->lenght; j++ ) {
            if( i != j ) {
                printf("🫥 ");
                for( int k = i; k < j; k++ ) {
                    printf("%c", string->cadena[k]);
                }
                printf("\n");
            }
        }
    }
}