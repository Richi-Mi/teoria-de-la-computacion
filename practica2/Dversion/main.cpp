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
        cout << i << ":" << endl;
        cout << "L" << i + 1 << ": ";
        for (const auto &palabra : Index[i]) {
            cout << palabra << " ";
        }
        cout << endl;
    }
}

// Función para concatenar dos lenguajes
vector<string> concatenarLenguajes(const vector<string> &L1, const vector<string> &L2) {
    vector<string> resultado;
    for (const auto &palabra1 : L1) {
        for (const auto &palabra2 : L2) {
            resultado.push_back(palabra1 + palabra2);
        }
    }
    return resultado;
}

// Función para unir dos lenguajes
vector<string> unirLenguajes(const vector<string> &L1, const vector<string> &L2) {
    vector<string> resultado = L1;
    resultado.insert(resultado.end(), L2.begin(), L2.end());
    return resultado;
}

// Función para calcular la potencia de un lenguaje
vector<string> potenciaLenguaje(const vector<string> &L, int exponente) {
    vector<string> resultado;

    if (exponente == 0) {
        resultado.push_back("λ");
        return resultado;
    }

    if (exponente > 0) {
        resultado = L;
        for (int i = 1; i < exponente; ++i) {
            vector<string> temp;
            for (const auto &p1 : resultado) {
                for (const auto &p2 : L) {
                    temp.push_back(p1 + p2);
                }
            }
            resultado = temp;
        }
    } else {
        if (find(L.begin(), L.end(), "λ") == L.end()) {
            cout << "No se puede calcular una potencia negativa si no está λ." << endl;
        } else {
            resultado.push_back("λ");
        }
    }

    return resultado;
}

// Función para calcular la cerradura de Kleene de un lenguaje
vector<string> cerraduraKleene(const vector<string> &L, int limite) {
    vector<string> resultado;
    resultado.push_back("λ");

    vector<string> actual = L;
    for (int i = 1; i <= limite; ++i) {
        resultado.insert(resultado.end(), actual.begin(), actual.end());
        actual = concatenarLenguajes(actual, L);
    }

    return resultado;
}

int main() {
    vector<vector<string>> Index;

    for (int i = 1; ; ++i) {
        string nombreArchivo = "A" + to_string(i) + ".txt";
        ifstream prueba(nombreArchivo);

        if (!prueba.is_open()) break;

        Index.push_back(cargarLenguaje(nombreArchivo));
    }

    int opcion;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Mostrar Lenguajes almacenados" << endl;
        cout << "2. Concatenar dos lenguajes" << endl;
        cout << "3. Unir dos lenguajes" << endl;
        cout << "4. Calcular la potencia de un lenguaje" << endl;
        cout << "5. Calcular la cerradura de Kleene de un lenguaje" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarLenguajes(Index);
                break;
            case 2: {
                int l1, l2;
                cout << "Ingrese los indices de los lenguajes a concatenar (ejemplo: 0 1): ";
                cin >> l1 >> l2;

                if (l1 >= 0 && l1 < Index.size() && l2 >= 0 && l2 < Index.size()) {
                    vector<string> resultado = concatenarLenguajes(Index[l1], Index[l2]);
                    for (const auto &palabra : resultado) {
                        cout << palabra << " ";
                    }
                    cout << endl;
                }
                break;
            }
            case 3: {
                int l1, l2;
                cout << "Ingrese los indices de los lenguajes a unir (ejemplo: 0 1): ";
                cin >> l1 >> l2;

                if (l1 >= 0 && l1 < Index.size() && l2 >= 0 && l2 < Index.size()) {
                    vector<string> nuevoLenguaje = unirLenguajes(Index[l1], Index[l2]);
                    Index.push_back(nuevoLenguaje);
                }
                break;
            }
            case 4: {
                int l, exponente;
                cout << "Ingrese el indice del lenguaje y la potencia (-5 a 10): ";
                cin >> l >> exponente;

                if (l >= 0 && l < Index.size()) {
                    vector<string> resultado = potenciaLenguaje(Index[l], exponente);
                    for (const auto &palabra : resultado) {
                        cout << palabra << " ";
                    }
                    cout << endl;
                }
                break;
            }
            case 5: {
                int l, limite;
                cout << "Ingrese el indice del lenguaje y el limite de la cerradura: ";
                cin >> l >> limite;

                if (l >= 0 && l < Index.size() && limite > 0) {
                    vector<string> resultado = cerraduraKleene(Index[l], limite);
                    for (const auto &palabra : resultado) {
                        cout << palabra << " ";
                    }
                    cout << endl;
                }
                break;
            }
            case 0:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
        }
    } while (opcion != 0);

    return 0;
}
