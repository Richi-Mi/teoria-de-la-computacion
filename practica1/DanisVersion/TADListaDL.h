// TADListaDL.h
/*
LIBRERIA: Cabecera del TAD Lista Doblemente Ligada
AUTOR: Daniela del Carmen Maldonado Bedolla
Grupo: 2CM3

Funciones y delcaracones de estructuras fueron modificadas a partir de la informaciÃ³n
proporcionada por: Edgardo AdriÃ¡n Franco MartÃ­nez (C) Noviembre 2022

VERSIÃ“N: 1.0
Diciembre 2023

DESCRIPCIÃ“N: TAD Lista Doblemente Ligada.
Estructura de datos que permite almacenar elementos en una secuencia
lineal, donde cada elemento estÃ¡ conectado al siguiente mediante punteros.

OBSERVACIONES: Una lista es una estructura que asigna
memoria conforme se necesite durante la ejecuciÃ³n del programa.
*/

#ifndef TADLISTADL_H
#define TADLISTADL_H

#define TRUE 1
#define FALSE 0

// DefiniciÃ³n de boolean
typedef unsigned char boolean;

// DefiniciÃ³n de un elemento (ajusta segÃºn tus necesidades)
typedef char* elemento;
/* 
//Definicion Longitud de lista
typedef int longitud; */

// Estructura de un nodo para lista doblemente ligada
typedef struct nodo {
    elemento e;
    /* longitud l; */
    
    // RelaciÃ³n con el nodo anterior
    struct nodo* anterior;
    // RelaciÃ³n con el nodo siguiente
    struct nodo* siguiente;
} nodo;

// Definir una posiciÃ³n como un apuntador a nodo
typedef nodo* posicion;

// Estructura de una lista
typedef struct lista {
    int tam;
    // PosiciÃ³n del frente de la lista
    posicion frente;
    // PosiciÃ³n del final de la lista
    posicion final;
} lista;

//OPERADORES DE CONSTRUCCIÃ“N
void Initialize(lista* L);      // Inicializar lista (Initialize)
void Destroy(lista* L);         // Eliminar lista (Destroy)

//OPERADORES DE POSICIONAMIENTO Y BÃšSQUEDA
posicion Final(lista L);                    // PosiciÃ³n del final de la lista (Final)
posicion First(lista L);                    // PosiciÃ³n del primero de la lista (First)
posicion Following(lista L, posicion P);    // PosiciÃ³n del siguiente de P en la lista (Following)
posicion Previous(lista L, posicion P);     // PosiciÃ³n del anterior a P en la lista (Previous)
posicion Search(lista L, elemento e);       // PosiciÃ³n del elemento en la lista (Search)       

//OPERADORES DE CONSULTA
elemento Position(lista L, posicion P);         // Elemento en la posiciÃ³n P de la lista
boolean ValidatePosition(lista L, posicion P);  // Validar posiciÃ³n en la lista
elemento Element(lista L, int n);               // Elemento en la posiciÃ³n n de la lista
int Size(lista L);                              // TamaÃ±o de la lista
boolean Empty(lista L);                         // Verificar si la lista estÃ¡ vacÃ­a

//OPERADORES DE MODIFICACIÃ“N
void Insert(lista* L, posicion P, elemento e, boolean b);   // Insertar elemento en la lista
void Add(lista* L, elemento e);                             // Agregar elemento al final de la lista
void Remove(lista* L, posicion P);                          // Remover elemento de la lista
void Replace(lista* L, posicion P, elemento e);             // Sustituir elemento en la lista

#endif // TADLISTADL_H