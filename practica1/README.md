# Practica 1. Operaciones con cadenas

Construir un programa en lenguaje de programación C capaz de recibir
como entrada dos cadenas de longitud menor a 50 caracteres
alfanuméricos (Alfabeto compuesto por números y letras).

* El programa deberá de permitir seleccionar entre operar ambas
cadenas o con solo una de ellas.

* El resultado de la operación entre cadenas generará una nueva cadena
con la que se podrá operar posteriormente, excepto para las
operaciones que generan una lista de cadenas (cálculo de prefijos,
sufijos y subcadenas).

* La generación de subsecuencias será omitida en la práctica.

* Las operaciones que generan nuevas cadenas para operar
son:
* * Concatenación
* * Potencia (Positiva y Negativa)

* Las operaciones que solo regresan resultados en pantalla
y/o archivo:
* * Generación de Prefijos
* * Generación de Sufijos
* * Generación de Subcadenas
* * Cálculo de la longitud de una cadena

## Instrucciones de ejecución

```Bash
gcc main.c lista.c -o main
./main
```