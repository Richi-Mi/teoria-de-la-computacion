#include <iostream>
#include <cstring>

using namespace std;

// Función para obtener el tamaño de un lenguaje sin necesidad de maxSize
int obtenerTamLenguaje(char L[][100]) {
    int tamano = 0;  // Reemplazado tamaño por tamano
    while (L[tamano][0] != '\0') {  // Verifica que no haya cadenas vacías
        tamano++;
    }
    return tamano;
}


// Cerradura positiva (L+)
void cerraduraPositiva(char L[][100], char resultado[][100], int sizeL, int &sizeResultado, int maxExponente) {
    int index = 0;

    // Verificar si el exponente es 1, solo imprimir el lenguaje original
    for (int exp = 1; exp <= maxExponente; exp++) {
        if (exp == 1) {
            // Solo se imprimen las palabras originales
            for (int i = 0; i < sizeL; i++) {
                strcpy(resultado[index++], L[i]);
            }
        } else {
            // Para exponentes mayores, se generan las concatenaciones
            for (int i = 0; i < sizeL; i++) {
                for (int j = 0; j < sizeL; j++) {
                    strcpy(resultado[index], L[i]);
                    for (int k = 1; k < exp; k++) {
                        strcat(resultado[index], L[j]);
                    }
                    index++;
                }
            }
        }
    }

    sizeResultado = index;
}

// Cerradura de Kleene (L*)
void cerraduraKleene(char L[][100], char resultado[][100], int sizeL, int &sizeResultado, int maxExponente) {
    int index = 0;

    // Agregar "λ" (lambda)
    strcpy(resultado[index++], "λ");

    // Verificar si el exponente es 1, solo imprimir el lenguaje original
    for (int exp = 1; exp <= maxExponente; exp++) {
        if (exp == 1) {
            // Solo se imprimen las palabras originales
            for (int i = 0; i < sizeL; i++) {
                strcpy(resultado[index++], L[i]);
            }
        } else {
            // Para exponentes mayores, se generan las concatenaciones
            for (int i = 0; i < sizeL; i++) {
                for (int j = 0; j < sizeL; j++) {
                    strcpy(resultado[index], L[i]);
                    for (int k = 1; k < exp; k++) {
                        strcat(resultado[index], L[j]);
                    }
                    index++;
                }
            }
        }
    }

    sizeResultado = index;
}

int main() {
    char L[6][100] = {"00", "10", "12", "45", "66", "77"};
    char resultado[10000][100];
    int sizeResultado;

    cerraduraPositiva(L, resultado, 6, sizeResultado, 3);
    cout << "CERRADURA POSITIVA \n" << "{";
    for (int i = 0; i < sizeResultado; i++) {
        cout << resultado[i] << ", ";
    }
    cout << "..." << "}" << endl;

    cerraduraKleene(L, resultado, 6, sizeResultado, 3);
    cout <<"\n\n CERRADURA KLEINE \n" << "{";
    for (int i = 0; i < sizeResultado; i++) {
        cout << resultado[i] << ", ";
    }
    cout << "..." << "}" << endl;

    int tam;
    tam = obtenerTamLenguaje(L);

    cerraduraPositiva(L, resultado, tam, sizeResultado, 3);
    cout << "CERRADURA POSITIVA MODIFICADA \n" << "{";
    for (int i = 0; i < sizeResultado; i++) {
        cout << resultado[i] << ", ";
    }
    cout << "..." << "}" << endl;

    cerraduraKleene(L, resultado, tam, sizeResultado, 3);
    cout <<"\n\n CERRADURA KLEINE MODIFICADA\n" << "{";
    for (int i = 0; i < sizeResultado; i++) {
        cout << resultado[i] << ", ";
    }
    cout << "..." << "}" << endl;

    return 0;
}
