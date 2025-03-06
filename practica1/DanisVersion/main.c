#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TADListaDL.h"

#define MAX 50

int readString(char *cadena);
void mostrar_menu();
void mostrar_cadenas(lista *listacadenas);
void subcadenas(char *cadena);

void prefijos(char *cadena);
void sufijos(char *cadena);

void potencia_positiva(char *cadena, int exponente, lista *listacadenas);
void potencia_negativa(char *cadena, int exponente) ;

int main() {
    char cadena1[MAX];
    char cadena2[MAX];

    int opcion;
    int posicion;
    char *cadena;
    int longitud;

    lista listacadenas;
    Initialize(&listacadenas);

    // Leer la primera cadena
    printf("Ingresar primera cadena: ");
    int l1 = readString(cadena1);
    if (l1 < 0) {
        printf("Error: Límite excedido para la cadena 1\n");
        exit(0);
    }
    Add(&listacadenas, cadena1);

    // Leer la segunda cadena
    printf("Ingresar segunda cadena: ");
    int l2 = readString(cadena2);
    if (l2 < 0) {
        printf("Error: Límite excedido para la cadena 2\n");
        exit(0);
    }
    Add(&listacadenas, cadena2);

    do {
        mostrar_menu();
        nodo *actual;

        // Leer la opción, asegurando entrada válida
        opcion = 0;
        while (opcion < 1 || opcion > 10) {
            printf("Ingrese el número de la opción: ");
            if (scanf("%d", &opcion) != 1) {
                opcion = 0; // Resetear si la entrada no es válida
                while (getchar() != '\n'); // Limpiar el búfer
            }
            while (getchar() != '\n'); // Limpiar el búfer
        }

        printf("\n");

        switch (opcion) {
            case 1:
                printf("Longitud de una cadena\n");
                
                
                printf("Cadenas almacenadas:\n");
                mostrar_cadenas(&listacadenas);
                
                printf("Seleccione la cadena de la que quiere conocer su longitud\n");
                scanf("%d", &posicion);

                // Validar que la posición esté dentro del rango
                if (posicion < 1 || posicion > listacadenas.tam) {
                    printf("Posición inválida. Intente de nuevo.\n");
                    break;
                }

                actual = listacadenas.frente;
                for (int i = 1; i < posicion; i++) {
                    actual = actual->siguiente;
                }

                longitud = strlen((char *)actual->e);

                printf("La longitud de la cadena %d es: %d", posicion, longitud);
                
                break;
            case 2:
                printf("Concatenar cadenas\n");

                // Mostrar las cadenas disponibles
                mostrar_cadenas(&listacadenas);

                // Solicitar la primera cadena
                printf("Seleccione la primera cadena a concatenar: ");
                scanf("%d", &posicion);
                if (posicion < 1 || posicion > listacadenas.tam) {
                    printf("Posición inválida. Intente de nuevo.\n");
                    break;
                }

                // Obtener el primer nodo
                actual = listacadenas.frente;
                for (int i = 1; i < posicion; i++) {
                    actual = actual->siguiente;
                }
                char *cadena1 = (char *)actual->e;

                // Solicitar la segunda cadena
                printf("Seleccione la segunda cadena a concatenar: ");
                scanf("%d", &posicion);
                if (posicion < 1 || posicion > listacadenas.tam) {
                    printf("Posición inválida. Intente de nuevo.\n");
                    break;
                }

                // Obtener el segundo nodo
                actual = listacadenas.frente;
                for (int i = 1; i < posicion; i++) {
                    actual = actual->siguiente;
                }
                char *cadena2 = (char *)actual->e;

                // Crear una nueva cadena concatenada
                char *nueva_cadena = (char *)malloc(strlen(cadena1) + strlen(cadena2) + 1);
                if (nueva_cadena == NULL) {
                    printf("Error al reservar memoria.\n");
                    break;
                }

                strcpy(nueva_cadena, cadena1);
                strcat(nueva_cadena, cadena2);

                // Imprimir el resultado
                printf("Resultado de la concatenación: %s\n", nueva_cadena);

                // Almacenar la nueva cadena en la lista
                Add(&listacadenas, nueva_cadena);

                break;
                
                case 3:
                printf("Potencia positiva de cadenas\n");
            
                // Mostrar las cadenas disponibles
                mostrar_cadenas(&listacadenas);
            
                // Solicitar la cadena a procesar
                printf("Seleccione una cadena para generar la potencia positiva: ");
                scanf("%d", &posicion);
            
                // Validar posición
                if (posicion < 1 || posicion > listacadenas.tam) {
                    printf("Posición inválida. Intente de nuevo.\n");
                    break;
                }
            
                // Obtener el nodo seleccionado
                actual = listacadenas.frente;
                for (int i = 1; i < posicion; i++) {
                    actual = actual->siguiente;
                }
                cadena = (char *)actual->e;
            
                // Solicitar el exponente
                int exponente;
                printf("Ingrese el exponente positivo: ");
                scanf("%d", &exponente);
            
                // Llamar a la función potencia positiva
                potencia_positiva(cadena, exponente, &listacadenas);
            
                break;
            
            case 4:
                printf("Potencia negativa de cadenas\n");
            
                // Mostrar las cadenas disponibles
                mostrar_cadenas(&listacadenas);
            
                // Solicitar la cadena a procesar
                printf("Seleccione una cadena para generar la potencia negativa: ");
                scanf("%d", &posicion);
            
                // Validar posición
                if (posicion < 1 || posicion > listacadenas.tam) {
                    printf("Posición inválida. Intente de nuevo.\n");
                    break;
                }
            
                // Obtener el nodo seleccionado
                actual = listacadenas.frente;
                for (int i = 1; i < posicion; i++) {
                    actual = actual->siguiente;
                }
                cadena = (char *)actual->e;
            
                // Solicitar el exponente
                int exponente_neg;
                printf("Ingrese el exponente negativo: ");
                scanf("%d", &exponente_neg);
            
                // Llamar a la función potencia negativa
                potencia_negativa(cadena, exponente_neg);
            
                break;
            
                case 5:
                printf("Generación de Prefijos\n");
            
                // Mostrar las cadenas disponibles
                mostrar_cadenas(&listacadenas);
            
                // Solicitar la cadena a procesar
                printf("Seleccione una cadena para generar los prefijos: ");
                scanf("%d", &posicion);
            
                // Validar posición
                if (posicion < 1 || posicion > listacadenas.tam) {
                    printf("Posición inválida. Intente de nuevo.\n");
                    break;
                }
            
                // Obtener el nodo seleccionado
                actual = listacadenas.frente;
                for (int i = 1; i < posicion; i++) {
                    actual = actual->siguiente;
                }
                cadena = (char *)actual->e;
            
                // Llamar a la función prefijos
                prefijos(cadena);
            
                break;
            
            case 6:
                printf("Sufijos\n");
            
                // Mostrar las cadenas disponibles
                mostrar_cadenas(&listacadenas);
            
                // Solicitar la cadena a procesar
                printf("Seleccione una cadena para generar los sufijos: ");
                scanf("%d", &posicion);
            
                // Validar posición
                if (posicion < 1 || posicion > listacadenas.tam) {
                    printf("Posición inválida. Intente de nuevo.\n");
                    break;
                }
            
                // Obtener el nodo seleccionado
                actual = listacadenas.frente;
                for (int i = 1; i < posicion; i++) {
                    actual = actual->siguiente;
                }
                cadena = (char *)actual->e;
            
                // Llamar a la función sufijos
                sufijos(cadena);
            
                break;
            

                case 7:
                printf("Subcadenas\n");

                // Mostrar las cadenas disponibles
                mostrar_cadenas(&listacadenas);

                // Solicitar la cadena a procesar
                printf("Seleccione una cadena para generar las subcadenas: ");
                scanf("%d", &posicion);

                // Validar posición
                if (posicion < 1 || posicion > listacadenas.tam) {
                    printf("Posición inválida. Intente de nuevo.\n");
                    break;
                }

                // Obtener el nodo seleccionado
                actual = listacadenas.frente;
                for (int i = 1; i < posicion; i++) {
                    actual = actual->siguiente;
                }
                cadena = (char *)actual->e;

                // Llamar a la función subcadenas
                subcadenas(cadena);

                break;

            
            case 8:
                printf("\n\nCadenas almacenadas en la lista.\n");
                mostrar_cadenas(&listacadenas);
                break;

            case 9:
                printf("Inversa de la cadena seleccionada\n");
            
                // Mostrar las cadenas disponibles
                mostrar_cadenas(&listacadenas);
            
                // Solicitar la cadena a procesar
                printf("Seleccione una cadena para obtener la inversa: ");
                scanf("%d", &posicion);
            
                // Validar posición
                if (posicion < 1 || posicion > listacadenas.tam) {
                    printf("Posición inválida. Intente de nuevo.\n");
                    break;
                }
            
                // Obtener el nodo seleccionado
                actual = listacadenas.frente;
                for (int i = 1; i < posicion; i++) {
                    actual = actual->siguiente;
                }
                cadena = (char *)actual->e;
            
                // Invertir la cadena
                int longitud = strlen(cadena);
                char inversa[MAX];
                int j = 0;
            
                // Copiar la cadena al revés
                for (int i = longitud - 1; i >= 0; i--) {
                    inversa[j++] = cadena[i];
                }
                inversa[j] = '\0'; // Agregar el terminador nulo
            
                // Imprimir la cadena invertida
                printf("\nInversa de la cadena seleccionada:\n");
                printf("%s\n", inversa);
            
                break;

            case 10:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
                break;
        }

    } while (opcion != 10);

    Destroy(&listacadenas);

    return 0;
}



// Función para leer una cadena
int readString(char *cadena) {
    int i = 0;
    char c;

    // Leer hasta salto de línea o fin de archivo
    while ((c = getchar()) != '\n' && c != EOF) {
        if (i < MAX - 1) {
            cadena[i++] = c;
        } else {
            return -1; // Excede el límite
        }
    }

    cadena[i] = '\0'; // Finalizar la cadena

    return i;
}

// Función para mostrar el menú
void mostrar_menu() {
    printf("\n\n--- Menú de Operaciones con Cadenas ---\n");
    printf("1. Longitud de una cadena\n");
    printf("2. Concatenar cadenas\n");
    printf("3. Potencia Positiva\n");
    printf("4. Potencia Negativa\n");
    printf("5. Generación de Prefijos\n");
    printf("6. Sufijos\n");
    printf("7. Subcadenas\n");
    printf("8. Cadenas almacenadas en la lista.\n");
    printf("9. Inversa de una cadena\n");
    printf("10. Salir\n");
    printf("\n");
}


void concatenar( lista listacadenas ){
    printf("Eliga las cadenas que desea utilizar");


}

// Función para mostrar el estado actual de la lista de cadenas
void mostrar_cadenas(lista *listacadenas) {
    printf("\nCadenas almacenadas en la lista:\n");

    int posicion = 1;
    nodo *actual = listacadenas->frente;

    while (actual != NULL) {
        printf("%d: %s\n", posicion++, (char *)actual->e);
        actual = actual->siguiente;
    }

    printf("\n\n");

    /* printf("Tamaño total de la lista: %d\n", listacadenas->tam); */
}

void prefijos(char *cadena) {
    int longitud = strlen(cadena);

    // Generar e imprimir los prefijos
    printf("\nPrefijos de la cadena seleccionada:\n");
    for (int i = 1; i <= longitud; i++) {
        char prefijo[MAX];
        strncpy(prefijo, cadena, i);
        prefijo[i] = '\0'; // Agregar terminador nulo
        printf("%s\n", prefijo);
    }
}

void sufijos(char *cadena) {
    int longitud = strlen(cadena);

    // Generar e imprimir los sufijos
    printf("\nSufijos de la cadena seleccionada:\n");
    for (int i = 0; i < longitud; i++) {
        printf("%s\n", cadena + i);
    }
}



void subcadenas(char *cadena) {
    int longitud = strlen(cadena);

    // Generar e imprimir todas las subcadenas posibles
    printf("\nSubcadenas de la cadena seleccionada:\n");

    // Iteramos sobre las posiciones de inicio
    for (int i = 0; i < longitud; i++) {
        // Iteramos sobre las posiciones de fin
        for (int j = i + 1; j <= longitud; j++) {
            // Imprimir la subcadena desde la posición i hasta j
            printf("%.*s\n", j - i, cadena + i);
        }
    }
}

void potencia_positiva(char *cadena, int exponente, lista *listacadenas) {
    // Validar exponente
    if (exponente < 1) {
        printf("El exponente debe ser positivo.\n");
        return;
    }

    // Crear un buffer para almacenar el resultado
    char resultado[MAX * exponente];
    resultado[0] = '\0'; // Inicializar la cadena vacía

    // Concatenar la cadena el número de veces especificado
    for (int i = 0; i < exponente; i++) {
        strcat(resultado, cadena);
    }

/*     Add()); */

    // Imprimir el resultado
    printf("\nPotencia positiva de la cadena seleccionada:\n");
    printf("%s\n", resultado);

}


void potencia_negativa(char *cadena, int exponente) {
    // Validar exponente
    if (exponente >= 0) {
        printf("El exponente debe ser negativo.\n");
        return;
    }

    // La potencia negativa simplemente deja la cadena vacía
    printf("\nPotencia negativa de la cadena seleccionada:\n");
    printf("\n"); // La cadena está vacía
}


