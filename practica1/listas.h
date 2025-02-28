#include <stdlib.h>
#include <stdio.h>

typedef struct Nodo {
    char *cadena;
    int lenght;

    struct Nodo *sig; 
} Nodo;

typedef struct List {
    
    struct Nodo *inicial;
    int lenght;

} List;

void addElement( List *list, char *cadena, int lenght );
void showElements( List lista );
void eraseList( List *list );
Nodo* getString( List *list, int n );