#include <iostream>
#include <cstring>

using namespace std;

// Función para concatenar dos lenguajes
void concatenarLenguajes(char L1[][100], char L2[][100], char resultado[][100], int sizeL1, int sizeL2, int &sizeResultado) {
    int index = 0;
    for (int i = 0; i < sizeL1; i++) {
        for (int j = 0; j < sizeL2; j++) {
            strcpy(resultado[index], L1[i]);
            strcat(resultado[index], L2[j]);
            index++;
        }
    }
    sizeResultado = index;
}

// Función para realizar la unión de dos lenguajes
void unirLenguajes(char L1[][100], char L2[][100], char resultado[][100], int sizeL1, int sizeL2, int &sizeResultado) {
    int index = 0;
    for (int i = 0; i < sizeL1; i++) {
        strcpy(resultado[index++], L1[i]);
    }
    for (int j = 0; j < sizeL2; j++) {
        strcpy(resultado[index++], L2[j]);
    }
    sizeResultado = index;
}

// Función para invertir una cadena
void invertirCadena(char cadena[], char resultado[]) {
    int len = strlen(cadena);
    for (int i = 0; i < len; i++) {
        resultado[i] = cadena[len - i - 1];
    }
    resultado[len] = '\0';
}

// Función para calcular el inverso de un lenguaje
void inversoLenguaje(char L[][100], char resultado[][100], int sizeL, int &sizeResultado) {
    for (int i = 0; i < sizeL; i++) {
        invertirCadena(L[i], resultado[i]);
    }
    sizeResultado = sizeL;
}

// Función para imprimir todo un lenguaje
void imprimirLenguaje(char L[][100], int size) {
    cout << "{ ";
    for (int i = 0; i < size; i++) {
        cout << L[i];
        if (i < size - 1) cout << ", ";
    }
    cout << " }" << endl;
}

// Función para imprimir un lenguaje con límite (máximo 5 ejemplos)
void imprimirLenguajeLimitado(char L[][100], int size) {
    cout << "{ ";
    for (int i = 0; i < size && i < 5; i++) {
        cout << L[i];
        if (i < size - 1 && i < 4) cout << ", ";
    }
    if (size > 5) cout << ", ...";
    cout << " }" << endl;
}

int main() {
    // Declaración de los lenguajes
    char L1[][100] = {"001AF", "10FFAA", "109012", " 667800"};
    char L2[][100] = {"00", "10", "12", "45", "66", "77"};
    char L3[][100] = {"1", "0", "3", "5", "6", "F", "A", "B", "C"};

    // Tamaños de los lenguajes
    int sizeL1 = sizeof(L1) / sizeof(L1[0]);
    int sizeL2 = sizeof(L2) / sizeof(L2[0]);
    int sizeL3 = sizeof(L3) / sizeof(L3[0]);

    // Resultados
    char resultado[1000][100];
    int sizeResultado = 0;

    // 1. (L1L2) U L3
    cout << "\n";
    concatenarLenguajes(L1, L2, resultado, sizeL1, sizeL2, sizeResultado);
    unirLenguajes(resultado, L3, resultado, sizeResultado, sizeL3, sizeResultado);
    cout << "(L1L2) U L3: ";
    imprimirLenguaje(resultado, sizeResultado);
    
    cout << "\n";
    // 2. (L1 U L2)L3
    char unionL1L2[500][100];
    int sizeUnion = 0;
    unirLenguajes(L1, L2, unionL1L2, sizeL1, sizeL2, sizeUnion);
    concatenarLenguajes(unionL1L2, L3, resultado, sizeUnion, sizeL3, sizeResultado);
    cout << "(L1 U L2)L3: ";
    imprimirLenguaje(resultado, sizeResultado);
    
    cout << "\n";
    // 3. L1^2 (completo)
    concatenarLenguajes(L1, L1, resultado, sizeL1, sizeL1, sizeResultado);
    cout << "L1^2: ";
    imprimirLenguaje(resultado, sizeResultado);
    
    cout << "\n";
    // 6. L1^-1 (completo)
    inversoLenguaje(L1, resultado, sizeL1, sizeResultado);
    cout << "L1^-1: ";
    imprimirLenguaje(resultado, sizeResultado);

    //7. L2^-1 U (L1 U L3)
    char inversoL2[100][100];
    int sizeInversoL2 = 0;
    inversoLenguaje(L2, inversoL2, sizeL2, sizeInversoL2);
    unirLenguajes(inversoL2, L1, resultado, sizeInversoL2, sizeL1, sizeResultado);
    unirLenguajes(resultado, L3, resultado, sizeResultado, sizeL3, sizeResultado);
    cout << "L2^-1 U (L1 U L3): ";
    imprimirLenguaje(resultado, sizeResultado);
    
    cout << "\n";
    return 0;
}
