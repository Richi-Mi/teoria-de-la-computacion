#ifndef MYSTRING_H  // Si MYSTRING_H no está definido...
#define MYSTRING_H  // Definir MYSTRING_H

typedef struct Letter {
    char letter;
    struct Letter *next;
} Letter;

typedef struct String {
    Letter *inicio;
    int length;
} String;

String* readString();
String* initString();
void showString(String *cadena);

String* concat( String *cadena1, String *cadena2 );
String* inverseString( String *cadena );
String* powString( String *cadena, int p );

#endif // Para evitar que se redefina la libreria.