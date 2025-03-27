#include "myString.h"

#ifndef LANGUAJE_H 
#define LANGUAJE_H  

typedef struct LanguajeNode {
    String *inicioCadena;

    struct LanguajeNode *next;
} LanguajeNode;

typedef struct Languaje {
    
    LanguajeNode *inicio;

    int length;
} Languaje;

Languaje* initLanguaje();
void addString( Languaje *lang, String *cadena );
void showLanguaje( Languaje *lang );

// Operaciones.
Languaje* languajeUnion( Languaje *l1, Languaje *l2 );
Languaje* languajeConcat( Languaje *l1, Languaje *l2 );
Languaje* invertLanguaje( Languaje *lang );
Languaje* powLanguaje( Languaje *lang, int p );

#endif