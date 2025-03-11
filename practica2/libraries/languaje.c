#include <stdlib.h>
#include <stdio.h>

#include "languaje.h"

Languaje* initLanguaje() {
    Languaje *newL = malloc( sizeof( Languaje ) );
    newL->inicio = NULL;
    newL->length = 0;

    return newL;
}
void addString( Languaje *lang, String *cadena ) {
    // Crear un nuevo nodo.
    LanguajeNode *nodel = malloc( sizeof( LanguajeNode ) );
    nodel->inicioCadena = cadena;
    nodel->next = NULL;

    // Si no hay ningun nodo agregarlo.
    if( lang->inicio == NULL ) {
        lang->inicio = nodel;
    }
    else {
        LanguajeNode *aux = lang->inicio;
        while( aux->next != NULL ) {
            aux = aux->next;
        }
        aux->next = nodel;
    }
}
void showLanguaje( Languaje *lang ) {
    LanguajeNode *aux = lang->inicio;

    while( aux != NULL ) {
        showString( aux->inicioCadena );
        aux = aux->next;
    }
}
Languaje* languajeUnion( Languaje *l1, Languaje *l2 ) {
    Languaje *newLang = initLanguaje();

    LanguajeNode *p = l1->inicio;
    while( p != NULL ) {
        addString( newLang, p->inicioCadena );
        p = p->next;
    }
    LanguajeNode *q = l2->inicio;
    while( q != NULL ) {
        addString( newLang, q->inicioCadena );
        q = q->next;
    }
    return newLang;
}
Languaje* languajeConcat( Languaje *l1, Languaje *l2 ) {
    Languaje *newLang = initLanguaje();

    LanguajeNode *p = l1->inicio;
    while( p != NULL ) {
        LanguajeNode *q = l2->inicio;
        while( q != NULL ) {
            String *c = concat( p->inicioCadena, q->inicioCadena );
            addString( newLang, c );
            q = q->next;
        }
        p = p->next;
    }
    return newLang;
}
Languaje* invertLanguaje( Languaje *lang ) {
    Languaje *newLang = initLanguaje();

    LanguajeNode *p = lang->inicio;
    while ( p != NULL ) {
        addString( newLang, inverseString( p->inicioCadena ) );
        p = p->next;        
    }
    return newLang;
}