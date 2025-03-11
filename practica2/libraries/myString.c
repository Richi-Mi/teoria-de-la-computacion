#include <stdlib.h>
#include <stdio.h>

#include "myString.h"

void addLetter(Letter **p, char letra) {
    Letter *nL = malloc(sizeof(Letter));
    nL->letter = letra;
    nL->next = NULL;

    if (*p == NULL)
        *p = nL;
    else {
        Letter *aux = *p;
        while (aux->next != NULL)
            aux = aux->next;

        aux->next = nL;
    }
}

String* initString() {
    String *newString = malloc(sizeof(String));
    newString->length = 0;
    newString->inicio = NULL;
    return newString;
}

String* readString() {
    String *newCad = initString();
    char c;

    while ((c = getchar()) != '\n' && c != EOF) {
        addLetter(&(newCad->inicio), c);
        newCad->length++;
    }

    return newCad;
}

void showString(String *cadena) {
    Letter *i = cadena->inicio;

    while (i != NULL) {
        printf("%c", i->letter);
        i = i->next;
    }
    printf("\n");
}

String* concat(String *cadena1, String *cadena2) {
    String *cadenaNueva = initString();
    Letter *aux1 = cadena1->inicio;
    Letter *aux2 = cadena2->inicio;

    while (aux1 != NULL) {
        addLetter(&(cadenaNueva->inicio), aux1->letter);
        aux1 = aux1->next;
        cadenaNueva->length++;
    }
    while (aux2 != NULL) {
        addLetter(&(cadenaNueva->inicio), aux2->letter);
        aux2 = aux2->next;
        cadenaNueva->length++;
    }

    return cadenaNueva;
}

// Invierte una cadena y devuelve una nueva
String* inverseString(String *cadena) {
    if (cadena == NULL || cadena->length == 0) return NULL;

    String *invString = initString();
    char *cadenaInvertida = (char*)malloc(cadena->length * sizeof(char));

    if (!cadenaInvertida) {
        printf("Error: No se pudo asignar memoria\n");
        return NULL;
    }

    int i = cadena->length - 1;
    Letter *p = cadena->inicio;

    while (p != NULL) {
        cadenaInvertida[i] = p->letter;
        i--;
        p = p->next;
    }

    for (i = 0; i < cadena->length; i++)
        addLetter(&(invString->inicio), cadenaInvertida[i]);

    invString->length = cadena->length;
    free(cadenaInvertida);  // Liberar memoria

    return invString;
}

void freeString(String *cadena) {
    if (cadena == NULL) return;

    Letter *aux = cadena->inicio;
    while (aux != NULL) {
        Letter *temp = aux;
        aux = aux->next;
        free(temp);
    }

    free(cadena);
}
String* powString(String *cadena, int p) {
    String *cadenaNueva = initString();

    if (p > 0) {
        for (int i = 0; i < p; i++) {
            String *newCad = concat(cadenaNueva, cadena);
            freeString(cadenaNueva);
            cadenaNueva = newCad;
        }
    } else if (p < 0) {
        // Invertimos una sola vez
        String *ci = inverseString(cadena);
        int l = -p;
        for (int i = 0; i < l; i++) {
            String *newCad = concat(cadenaNueva, ci);
            freeString(cadenaNueva); 
            cadenaNueva = newCad;
        }
        freeString(ci);
    }

    return cadenaNueva;
}
