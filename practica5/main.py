from graphviz import Digraph
from collections import deque

def readInfo( line ):
    return line.strip().split(" ")

def draw_afd(afd_states, afd_initial, afd_finals, afd_transitions, alphabet, filename="afd"):
    dot = Digraph(comment="AFD")

    # Dibujar nodo ficticio para la flecha del estado inicial
    dot.node("", shape="none")

    for state in afd_states:
        shape = "doublecircle" if state in afd_finals else "circle"
        dot.node(state, shape=shape)

    # Flecha del nodo ficticio al estado inicial
    dot.edge("", afd_initial)

    # Agregar transiciones
    for state, targets in afd_transitions.items():
        for symbol_index, destination in enumerate(targets):
            symbol = alphabet[symbol_index]
            if destination != "-":
                dot.edge(state, destination, label=symbol)

    # Guardar como PNG
    dot.render(filename=filename, format="png", cleanup=True)
    print(f"\n✔ Grafo guardado como '{filename}.png'")


def get_afn_transition(state, symbol, transitions, alphabet):
    try:
        index = alphabet.index(symbol)
        value = transitions[state][index]
        return set(value.split(",")) if value != "-" else set()
    except:
        return set()

def determinize_afn(states, initialState, finalStates, alphabet, transitions):
    afd_states = []                         # Nuevos estados del AFD
    afd_transitions = {}                    # Transiciones del AFD
    afd_final_states = set()                # Estados finales del AFD
    visited = set()                         # Ya procesados
    queue = deque()                         # Estados pendientes

    # El estado inicial del AFD es el conjunto con el estado inicial del AFN
    initial_set = frozenset([initialState])
    queue.append(initial_set)
    visited.add(initial_set)
    afd_states.append(initial_set)

    while queue:
        current = queue.popleft()
        current_name = ",".join(sorted(current))  # Nombre del nuevo estado AFD
        afd_transitions[current_name] = []

        for symbol in alphabet:
            # Obtener el conjunto de destinos desde todos los estados actuales
            new_state = set()
            for substate in current:
                new_state |= get_afn_transition(substate, symbol, transitions, alphabet)
            new_state_frozen = frozenset(new_state)

            if not new_state:
                afd_transitions[current_name].append("-")
            else:
                state_name = ",".join(sorted(new_state))
                afd_transitions[current_name].append(state_name)

                if new_state_frozen not in visited:
                    visited.add(new_state_frozen)
                    queue.append(new_state_frozen)
                    afd_states.append(new_state_frozen)

    # Detectar estados finales en el AFD
    for s in afd_states:
        if any(f in s for f in finalStates):
            afd_final_states.add(",".join(sorted(s)))

    return [",".join(sorted(s)) for s in afd_states], ",".join(sorted(initial_set)), list(afd_final_states), afd_transitions


# Pedimos el nombre del archivo donde definimos el automata.
print("Ingresa archivo donde esta el automata: ")
fileName = input()

# Intentamos abrir el archivo.
try:
    with open(fileName, "r") as file:
        lines = file.readlines()
        # La primera linea seran los estados.
        states = readInfo(lines[0])
        # La segunda el estado inicial.
        initialState = lines[1].strip()
        # La tercera los estados finales.
        finalStates = readInfo(lines[2])
        # La 4 los simbolos del alfabeto.
        alphabet = readInfo(lines[3])

        # Creamos diccionario vacio
        transitions = {}
        i = 0

        # A partir de la 5, las transiciones.
        for line in lines[4:]:
            transitions[ states[i] ] = readInfo(line)
            i = i + 1
        
        afd_states, afd_initial, afd_finals, afd_transitions = determinize_afn(
            states, initialState, finalStates, alphabet, transitions
        )

        print("\n=== AFD generado ===")
        print("Estados:", afd_states)
        print("Estado inicial:", afd_initial)
        print("Estados finales:", afd_finals)
        print("Transiciones:")

        print(f"SY -> {alphabet}")
        for state in afd_states:
            print(f"{state} -> {afd_transitions[state]}")
        
        draw_afd(afd_states, afd_initial, afd_finals, afd_transitions, alphabet)
        
except FileNotFoundError:
    print(" X - Archivo no encontrado")
    exit(1)
except Exception:
    print(" X - Ocurrio un error inesperado.")
    exit(1)
        