// TADListaDL.c

#include "TADListaDL.h"
#include <stddef.h>
#include <stdlib.h>

// DEFINICIONES DE FUNCIONES

//*************OPERADORES DE CONSTRUCCIÓN************

/*
void Initialize(lista* L);
Descripción: Inicializar lista (Iniciar una lista para su uso)
Recibe: lista* L (Referencia a la lista "L" a operar)
Devuelve: -
Observaciones: El usuario ha creado una lista y L tiene la referencia a ella.
*/
void Initialize(lista* L) {
    L->tam = 0;
    L->frente = NULL;
    L->final = NULL;
}

/*
void Destroy(lista* L);
Descripción: Eliminar lista (Libera la memoria asociada a la lista)
Recibe: lista* L (Referencia a la lista "L" a operar)
Devuelve: -
Observaciones: La lista L queda vacía y la memoria utilizada es liberada.
*/
void Destroy(lista* L) {
    // Liberar cada nodo de la lista
    while (L->frente != NULL) {
        posicion temp = L->frente;
        L->frente = L->frente->siguiente;
        free(temp);
    }

    // Reiniciar la lista
    L->tam = 0;
    L->frente = NULL;
    L->final = NULL;
}

//*******OPERADORES DE POSICIONAMIENTO Y BÚSQUEDA*******

/*
posicion Fin(lista L);
Descripción: Posición del final de la lista (Retorna la posición del elemento al final de la lista)
Recibe: lista L (Lista a operar)
Devuelve: posicion (Posición al final de la lista)
Observaciones: -
*/
posicion Final(lista L) {
    return L.final;
}

/*
posicion First(lista L);
Descripción: Posición del primero de la lista (Retorna la posición del elemento al inicio de la lista)
Recibe: lista L (Lista a operar)
Devuelve: posicion (Posición al inicio de la lista)
Observaciones: -
*/
posicion First(lista L) {
    return L.frente;
}

/*
posicion Following(lista L, posicion P);
Descripción: Posición del siguiente de P en la lista (Retorna la posición del elemento siguiente a P)
Recibe: lista L (Lista a operar), posicion P (Posición de referencia)
Devuelve: posicion (Posición siguiente a P)
Observaciones: La posición P debe ser válida en la lista L y no debe ser la posición final.
*/
posicion Following(lista L, posicion P) {
    if (P != NULL && P != L.final) {
        return P->siguiente;
    } else {
        return NULL; // P no es válida o es la posición final
    }
}

/*
posicion Previous(lista L, posicion P);
Descripción: Posición del anterior a P en la lista (Retorna la posición del elemento anterior a P)
Recibe: lista L (Lista a operar), posicion P (Posición de referencia)
Devuelve: posicion (Posición anterior a P)
Observaciones: La posición P debe ser válida en la lista L y no debe ser la posición frente.
*/
posicion Previous(lista L, posicion P) {
    if (P != NULL && P != L.frente) {
        return P->anterior;
    } else {
        return NULL; // P no es válida o es la posición frente
    }
}

/*
posicion Search(lista L, elemento e);
Descripción: Posición del elemento en la lista (Retorna la posición del elemento que coincida exactamente con e)
Recibe: lista L (Lista a operar), elemento e (Elemento a buscar)
Devuelve: posicion (Posición del elemento en la lista)
Observaciones: Si el elemento no se encuentra en la lista, retorna NULL.
*/
posicion Search(lista L, elemento e) {
    posicion actual = L.frente;

    while (actual != NULL) {
        if (actual->e == e) {
            return actual; // Elemento encontrado
        }
        actual = actual->siguiente;
    }

    return NULL; // Elemento no encontrado
}

//*********OPERADORES DE CONSULTA*********

/*
elemento Position(lista L, posicion P);
Descripción: Elemento en la posición P de la lista (Retorna el elemento en la posición P)
Recibe: lista L (Lista a operar), posicion P (Posición de referencia)
Devuelve: elemento (Elemento en la posición P)
Observaciones: La lista L es no vacía y la posición P es una posición válida.
*/
elemento Position(lista L, posicion P) {
    return P->e;
}

/*
boolean ValidatePosition(lista L, posicion P);
Descripción: Validar posición en la lista (Devuelve TRUE si la posición es válida en la lista L y FALSE en caso contrario)
Recibe: lista L (Lista a operar), posicion P (Posición a validar)
Devuelve: boolean (TRUE si la posición es válida, FALSE en caso contrario)
Observaciones: -
*/
boolean ValidatePosition(lista L, posicion P) {
    if (P != NULL && L.frente != NULL && L.final != NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*
elemento Element(lista L, int n);
Descripción: Elemento en la posición n de la lista (Devuelve el elemento en la posición n de la lista)
Recibe: lista L (Lista a operar), int n (Índice de la posición a consultar)
Devuelve: elemento (Elemento en la posición n de la lista)
Observaciones: Si la lista está vacía o el índice está fuera del tamaño de la lista, produce un error.
*/
elemento Element(lista L, int n) {
    if (n < 1 || n > L.tam) {
        // Índice fuera de rango, producir un error (podría ser una excepción)
        exit(EXIT_FAILURE);
    }

    posicion actual = L.frente;
    for (int i = 1; i < n; i++) {
        actual = actual->siguiente;
    }

    return actual->e;
}

/*
int Size(lista L);
Descripción: Tamaño de la lista (Devuelve el tamaño de la lista)
Recibe: lista L (Lista a operar)
Devuelve: int (Tamaño de la lista)
Observaciones: -
*/
int Size(lista L) {
    return L.tam;
}

/*
boolean Empty(lista L);
Descripción: Verificar si la lista está vacía (Devuelve TRUE si la lista está vacía y FALSE en caso contrario)
Recibe: lista L (Lista a operar)
Devuelve: boolean (TRUE si la lista está vacía, FALSE en caso contrario)
Observaciones: -
*/
boolean Empty(lista L) {
    return L.tam == 0 ? TRUE : FALSE;
}

//*************OPERADORES DE MODIFICACIÓN************

/*
void Insert(lista *L, posicion P, elemento e, boolean b);
Descripción: Insertar elemento en la lista (Inserta el elemento e en la posición anterior de P si b es verdadero,
o en la posición siguiente de P en caso contrario)
Recibe: lista *L (Referencia a la lista), posicion P (Posición de referencia), elemento e (Elemento a insertar),
boolean b (Indica si se inserta antes o después de P)
Devuelve: -
Observaciones: La posición P es una posición válida.
*/
void Insert(lista* L, posicion P, elemento e, boolean b) {
    nodo* nuevoNodo = (nodo*)malloc(sizeof(nodo));
    if (nuevoNodo == NULL) {
        // Manejo de error: no se pudo asignar memoria
        exit(EXIT_FAILURE);
    }

    nuevoNodo->e = e;

    if (b && P != NULL) {
        // Insertar antes de P
        nuevoNodo->siguiente = P;
        nuevoNodo->anterior = P->anterior;
        if (P->anterior != NULL) {
            P->anterior->siguiente = nuevoNodo;
        } else {
            L->frente = nuevoNodo;
        }
        P->anterior = nuevoNodo;
    } else {
        // Insertar después de P (o al frente de la lista)
        nuevoNodo->anterior = P;
        nuevoNodo->siguiente = P != NULL ? P->siguiente : NULL;
        if (P != NULL && P->siguiente != NULL) {
            P->siguiente->anterior = nuevoNodo;
        } else {
            L->final = nuevoNodo;
        }
        if (P == NULL) {
            L->frente = nuevoNodo;
        } else {
            P->siguiente = nuevoNodo;
        }
    }

    L->tam++;
}

/*
void Add(lista *L, elemento e);
Descripción: Agregar elemento al final de la lista (Agrega el elemento e al final de la lista)
Recibe: lista *L (Referencia a la lista), elemento e (Elemento a agregar)
Devuelve: -
Observaciones: -
*/
void Add(lista* L, elemento e) {
    Insert(L, L->final, e, FALSE);
}

/*
void Remove(lista *L, posicion P);
Descripción: Remover elemento de la lista (Remueve el elemento en la posición P de la lista)
Recibe: lista *L (Referencia a la lista), posicion P (Posición a remover)
Devuelve: -
Observaciones: La lista L es no vacía y la posición P es una posición válida.
*/
void Remove(lista* L, posicion P) {
    if (P->anterior != NULL) {
        P->anterior->siguiente = P->siguiente;
    } else {
        L->frente = P->siguiente;
    }

    if (P->siguiente != NULL) {
        P->siguiente->anterior = P->anterior;
    } else {
        L->final = P->anterior;
    }

    free(P);
    L->tam--;
}

/*
void Replace(lista *L, posicion P, elemento e);
Descripción: Sustituir elemento en la lista (Sustituye el elemento en la posición P por el elemento e)
Recibe: lista *L (Referencia a la lista), posicion P (Posición a sustituir), elemento e (Nuevo elemento)
Devuelve: -
Observaciones: La lista L es no vacía y la posición P es una posición válida.
*/
void Replace(lista* L, posicion P, elemento e) {
    P->e = e;
}

