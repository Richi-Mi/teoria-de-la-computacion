#include <stdlib.h>
#include <stdio.h>

#include "listas.h"

void addElement( List *list, char *cadena, int lenght ) {
    Nodo *nuevo = (Nodo *) malloc( sizeof( Nodo ) );

    nuevo -> cadena = cadena;
    nuevo -> lenght = lenght;
    nuevo -> sig = NULL;

    if( list -> inicial == NULL ) {
        list -> inicial = nuevo;
        list -> lenght++;
    }
    else {
        Nodo *aux = list -> inicial;
        while( aux -> sig != NULL ) {
            aux = aux -> sig;
        }
        aux -> sig = nuevo;
        list -> lenght++;
    }
}
void showElements( List lista ) {
    Nodo *aux = lista.inicial;
    int i = 0;
    while( aux != NULL ) {
        printf(" %d. -  %s de longitud: %d \n", i, aux -> cadena, aux->lenght );
        aux = aux -> sig;
        i++;
    }
}
void eraseList( List *list ) {
    Nodo *aux = list -> inicial;
    
    while( aux != NULL ) {
        list -> inicial = list -> inicial -> sig;
        free( aux );

        aux = list -> inicial;
    }
}
Nodo* getString(List *list, int n) {
    int i = 0;
    Nodo *aux = list->inicial;
    
    while (i < n && aux != NULL) {
        aux = aux->sig;
        i++;
    }
    
    if (aux == NULL) {
        return NULL; 
    }
    
    return aux;
}