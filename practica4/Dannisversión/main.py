from graphviz import Digraph
import os

# 🔧 Forzamos manualmente el path a Graphviz para que funcione correctamente
os.environ["PATH"] += os.pathsep + "C:\\Program Files\\Graphviz\\bin"

# Pedimos el nombre del archivo donde definimos el autómata.
print("Ingresa archivo donde está el autómata: ")
fileName = input()

def readInfo(list, index):
    return list[index].strip().split(" ")

def draw_automaton(transitions, initialState, finalStates):
    dot = Digraph()
    dot.attr(rankdir='LR')  # Dirección de izquierda a derecha

    dot.node('', shape="none")  # Nodo invisible para el inicio

    # Extraer estados únicos
    estados = set()
    for (origin, symbol), destination in transitions.items():
        estados.add(origin)
        estados.add(destination)

    # Agregar nodos
    for state in estados:
        if state in finalStates:
            dot.node(state, shape="doublecircle")
        else:
            dot.node(state, shape="circle")

    # Flecha de inicio
    dot.edge('', initialState)

    # Agregar transiciones
    for (origin, symbol), destination in transitions.items():
        dot.edge(origin, destination, label=symbol)

    # Renderizar el grafo
    dot.render('automata', format='png', cleanup=True)
    print("✅ Imagen del autómata generada como 'automata.png'")

# Intentamos abrir el archivo
try:
    with open(fileName, "r") as file:
        lines = file.readlines()
        alphabet = readInfo(lines, 0)
        states = lines[1].strip()
        initialState = lines[2].strip()
        finalStates = readInfo(lines, 3)
        transitions = {}

        for line in lines[4:]:
            fun = line.strip().split(" ")
            origin, symbol = fun[0].split(",")
            transitions[(origin, symbol)] = fun[1]

        print(" * Autómata cargado.")
        for key, value in transitions.items():
            print(f"{key} -> {value}")

        draw_automaton(transitions, initialState, finalStates)

except FileNotFoundError:
    print(" X - Archivo no encontrado")
    exit(1)
except Exception as e:
    print(" X - Ocurrió un error inesperado:", e)
    exit(1)

def verifyInput(cadena):
    currentState = initialState
    for symbol in cadena:
        if symbol not in alphabet:
            return False
        key = (currentState, symbol)
        if key not in transitions:
            return False
        currentState = transitions[key]
    return currentState in finalStates

# Verificación de cadenas
print(" * Ingrese cadenas para validar el autómata. (Escribe 'SALIR' para terminar)")
cadena = ""
while cadena.upper() != "SALIR":
    cadena = input()
    if cadena.upper() == "SALIR":
        break
    if verifyInput(cadena):
        print(" 0 - CADENA VÁLIDA.")
    else:
        print(" X - Cadena inválida.")
