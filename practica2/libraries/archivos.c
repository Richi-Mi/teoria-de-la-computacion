#include <stdio.h>

#include "archivos.h"
#include "languaje.h"

Languaje* readFileAndGetLanguaje( char route[] ) {
    FILE *archivo = fopen( route, "r"); 

    if( archivo == NULL ) {
        perror("Error al abrir el archivo");
        return NULL; // TODO: devolver null
    }
    
    char c;
    Languaje *lang = initLanguaje();
    String *cadenaActual = initString();

    while ( ( c = fgetc(archivo) ) != EOF ) {
        if( c != ',' ) {
            addLetter( &( cadenaActual->inicio ), c );
        }
        else {
            addString( lang, cadenaActual );
            cadenaActual = initString();
        }
    }
    addString( lang, cadenaActual );

    fclose( archivo );

    return lang;
}
void saveLanguaje( char route[], Languaje *lang ) {
    FILE *archivo = fopen( route, "w");

    if( archivo == NULL ) {
        perror("Error al abrir el archivo");
        return; // TODO: devolver null
    }

    LanguajeNode *p = lang->inicio;
    
    while( p != NULL ) {
        Letter *ltnode = p->inicioCadena->inicio;
        while( ltnode != NULL ) {
            fputc( ltnode->letter, archivo );
            ltnode = ltnode->next;
        }
        if( p->next != NULL ) {
            fputc(',', archivo);
        }
        p = p->next;
        
    }
    fclose(archivo);
}