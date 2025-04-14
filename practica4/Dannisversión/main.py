from graphviz import Digraph
import os
from collections import defaultdict

# 🔧 Aseguramos el path a Graphviz
os.environ["PATH"] += os.pathsep + "C:\\Program Files\\Graphviz\\bin"

print("Ingresa archivo donde está el autómata: ")
fileName = input()

def readInfo(lines, index):
    return lines[index].strip().split(" ")

def draw_automaton(transitions, initialState, finalStates):
    dot = Digraph()
    dot.attr(rankdir='LR', fontname='Helvetica')  # Dirección y fuente

    # ⚙️ Estilo de flechas
    dot.attr('edge', color='gray30', penwidth='2.2', fontcolor='black')

    dot.node('', shape="none")  # Nodo invisible de inicio

    # Extraer estados únicos
    estados = set()
    for (origin, symbol), destination in transitions.items():
        estados.update([origin, destination])

    # Todos los estados con el mismo estilo naranja
    for state in estados:
        # Si el estado es final, le ponemos el doble círculo
        if state in finalStates:
            dot.node(state, shape="doublecircle", style='filled', fillcolor='orange', fontname='Helvetica')
        else:
            dot.node(state, shape="circle", style='filled', fillcolor='orange', fontname='Helvetica')

    dot.edge('', initialState)  # Flecha de inicio

    # Agrupar transiciones
    edges = defaultdict(list)
    for (origin, symbol), destination in transitions.items():
        edges[(origin, destination)].append(symbol)

    for (origin, destination), symbols in edges.items():
        dot.edge(origin, destination, label=",".join(symbols), fontname='Helvetica')

    dot.render('automata', format='png', cleanup=True)
    print("✅ Imagen del autómata generada como 'automata.png'")

# Carga del archivo
try:
    with open(fileName, "r") as file:
        lines = file.readlines()
        alphabet = readInfo(lines, 0)
        states = lines[1].strip()
        initialState = lines[2].strip()
        finalStates = readInfo(lines, 3)
        transitions = {}

        for line in lines[4:]:
            if not line.strip():
                continue
            origin, symbol = line.strip().split(" ")[0].split(",")
            destination = line.strip().split(" ")[1]
            transitions[(origin, symbol)] = destination

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
while True:
    cadena = input()
    if cadena.upper() == "SALIR":
        break
    if verifyInput(cadena):
        print(" ✅ - 0 - CADENA VÁLIDA.")
    else:
        print(" ❌- X - Cadena inválida.")
