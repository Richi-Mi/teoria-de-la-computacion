#include <bits/stdc++.h>
using namespace std;

// Función para cargar un lenguaje desde un archivo
vector<string> cargarLenguaje(const string &nombreArchivo) {
    vector<string> lenguaje;
    ifstream archivo(nombreArchivo);
    string palabra;

    if (archivo.is_open()) {
        while (archivo >> palabra) {
            lenguaje.push_back(palabra);
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    }

    return lenguaje;
}

// Función para mostrar los lenguajes almacenados
void mostrarLenguajes(const vector<vector<string>> &Index) {
    for (size_t i = 0; i < Index.size(); ++i) {
        cout << "L" << i + 1 << ": ";
        for (const auto &palabra : Index[i]) {
            cout << palabra << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<string>> Index; // Lista principal

    // Cargar los archivos A1, A2, A3, etc.
    for (int i = 1; ; ++i) {
        string nombreArchivo = "A" + to_string(i) + ".txt";
        ifstream prueba(nombreArchivo);

        if (!prueba.is_open()) break; // Salir si no hay más archivos

        Index.push_back(cargarLenguaje(nombreArchivo));
    }

    int opcion;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Mostrar Lenguajes almacenados" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarLenguajes(Index);
                break;
            case 0:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
        }
    } while (opcion != 0);

    return 0;
}
