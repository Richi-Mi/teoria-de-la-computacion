#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "listas.h"

#define MAX 50

int readString(char *cadena);
void inverseString(Nodo *cadena, char *result);
void showMenu();

void concat(List *lista);
void strPow(List *lista);
void inverse(List *lista);
void prefijos(List *lista);
void sufijos(List *lista);
void subcadenas(List *lista);

int main() {
    char palabra1[MAX];
    char palabra2[MAX];
    
    printf("Ingrese la cadena x: ");
    int l1 = readString(palabra1);
    printf("Ingrese la cadena y: ");
    int l2 = readString(palabra2);

    List listaCadenas;
    listaCadenas.inicial = NULL;
    listaCadenas.lenght = 0;

    addElement(&listaCadenas, palabra1, l1);
    addElement(&listaCadenas, palabra2, l2);

    int option = 0;

    do {
        showMenu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                concat(&listaCadenas);
                break;
            case 2:
                prefijos(&listaCadenas);
                break;
            case 3:
                sufijos(&listaCadenas);
                break;
            case 4:
                inverse(&listaCadenas);
                break;
            case 5:
                strPow(&listaCadenas);
                break;
            case 6:
                showElements(listaCadenas);
                break;
            case 7:
                subcadenas(&listaCadenas);
                break;
            default:
                option = 0;
                break;
        }
    } while (option != 0);

    eraseList(&listaCadenas);
}

int readString(char *cadena) {
    int i = 0;
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (i < MAX - 1) {
            cadena[i++] = c;
        }
    }
    cadena[i] = '\0';
    return i;
}

void showMenu() {
    printf("\n*--------------------------------*\n");
    printf("1. Concatenación de las cadenas \n");
    printf("2. Prefijos de una cadena       \n");
    printf("3. Sufijos de una cadena        \n");
    printf("4. Inversión de una cadena      \n");
    printf("5. Potencia de una cadena       \n");
    printf("6. Ver cadenas                  \n");
    printf("7. Obtener todas las subcadenas \n");
    printf("0. Salir                        \n");
    printf("*--------------------------------*\n");
}

void concat(List *lista) {
    printf("Escoje el indice de las cadenas que vas a concatenar: \nFormato: (indice1, indice2)\n");
    int i1, i2; 
    scanf("%d,%d", &i1, &i2);

    Nodo *cad1 = getString(lista, i1);
    Nodo *cad2 = getString(lista, i2);

    int newLength = cad1->lenght + cad2->lenght + 1;
    char *newCad = (char *)malloc(newLength * sizeof(char));
    if (!newCad) return;

    strcpy(newCad, cad1->cadena);
    strcat(newCad, cad2->cadena);
    addElement(lista, newCad, newLength);
    printf("Cadena agregada: %s\n", newCad);
}

void strPow(List *lista) {
    printf("Ingrese el indice de la cadena, y el indice a elevarla: \nFormato: (iCad, iPow)\n");
    int iCad, iPow, i;
    scanf("%d,%d", &iCad, &iPow);

    Nodo *cad = getString(lista, iCad);
    if (!cad) return;

    int length = (cad->lenght * abs(iPow)) + 1;
    char *newCad = (char *)malloc(length * sizeof(char));
    if (!newCad) return;

    newCad[0] = '\0';
    for (i = 0; i < abs(iPow); i++) {
        strcat(newCad, cad->cadena);
    }

    addElement(lista, newCad, length - 1);
    printf("Cadena agregada: %s\n", newCad);
}

void inverseString(Nodo *cadena, char *result) {
    int i, j = 0;
    for (i = cadena->lenght - 1; i >= 0; i--) {
        result[j++] = cadena->cadena[i];
    }
    result[j] = '\0';
}

void inverse(List *lista) {
    printf("Ingrese el indice de la cadena a invertir: ");
    int opt;
    scanf("%d", &opt);

    Nodo *string = getString(lista, opt);
    if (!string) return;

    char *inverseCad = (char *)malloc((string->lenght + 1) * sizeof(char));
    if (!inverseCad) return;

    inverseString(string, inverseCad);
    printf("Cadena invertida: %s\n", inverseCad);
}

void prefijos(List *lista) {
    int index, i, j;
    printf("Ingresa el indice de la cadena a procesar: ");
    scanf("%d", &index);

    Nodo *string = getString(lista, index);
    if (!string) return;

    for (i = 0; i <= string->lenght; i++) {
        for (j = 0; j < i; j++) {
            printf("%c", string->cadena[j]);
        }
        printf("\n");
    }
}

void sufijos(List *lista) {
    int index, i, j;
    printf("Ingresa el indice de la cadena a procesar: ");
    scanf("%d", &index);

    Nodo *string = getString(lista, index);
    if (!string) return;

    for (i = string->lenght; i >= 0; i--) {
        for (j = i; j < string->lenght; j++) {
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
        for( int j = i; j < string->lenght; j++ ) {
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