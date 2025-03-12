#include <stdio.h>
#include <stdlib.h>

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
        if( c != '\n' ) {
            addLetter( &( cadenaActual->inicio ), c );
            cadenaActual->length++;
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
            fputc('\n', archivo);
        }
        p = p->next;
        
    }
    fclose(archivo);
}
char* getFileName( char* operation, int index ) {
    char *filename = malloc( 100 * sizeof(char));
    if (filename == NULL) {
        return NULL;  // Manejo de error si la asignación falla
    }

    snprintf(filename, 100, "./build/%s_%d.txt", operation, index);  // Construye el nombre del archivo
    return filename;
}