from graphviz import Digraph
from collections import deque

# Pedimos el nombre del archivo donde definimos el automata.
print("Ingresa archivo donde esta el automata: ")
fileName = input()

def readInfo( list, index ):
    # Regresamos la información como lista.
    return list[index].strip().split(" ")

def draw_automaton(transitions, initialState, finalStates):
    dot = Digraph()
    dot.attr(rankdir='LR')  # Dirección de izquierda a derecha

    dot.node('', shape="none")  # Nodo invisible para el inicio

    # Convertimos los conjuntos de estados a strings para visualización
    def state_name(state):
        if isinstance(state, frozenset):
            if not state:
                return "{}"  # Conjunto vacío
            return "{" + ",".join(sorted(state)) + "}"
        return str(state)

    # Extraer estados únicos
    estados = set()
    for (origin, symbol), destination in transitions.items():
        estados.add(origin)
        estados.add(destination)

    # Agregar nodos
    for state in estados:
        name = state_name(state)
        if state in finalStates:
            dot.node(name, shape="doublecircle")
        else:
            dot.node(name, shape="circle")

    # Flecha de inicio
    dot.edge('', state_name(initialState))

    # Agregar transiciones
    for (origin, symbol), destination in transitions.items():
        dot.edge(state_name(origin), state_name(destination), label=symbol)

    # Renderizar
    dot.render('automata', format='png', cleanup=True)
    print("✅ Imagen del autómata generada como 'automata.png'")

def compute_epsilon_closure(state, transitions):
    closure = set()
    stack = [state]
    
    while stack:
        current = stack.pop()
        if current not in closure:
            closure.add(current)
            key = (current, '-')
            if key in transitions:
                dest = transitions[key]
                if isinstance(dest, str):
                    if dest != '-':
                        stack.append(dest)
                elif isinstance(dest, list):
                    for d in dest:
                        if d != '-':
                            stack.append(d)
    return closure

def afn_to_afd_with_epsilon(transitions, alphabet, initialState, finalStates):
    afd_transitions = {}
    afd_states = []
    afd_finals = set()

    initial_closure = frozenset(compute_epsilon_closure(initialState, transitions))
    afd_initial = initial_closure
    queue = deque([initial_closure])
    visited = set()

    while queue:
        current_set = queue.popleft()
        if current_set in visited:
            continue
        visited.add(current_set)
        afd_states.append(current_set)

        # ¿Es estado final?
        if any(state in finalStates for state in current_set):
            afd_finals.add(current_set)

        for symbol in alphabet:
            next_states = set()
            for state in current_set:
                key = (state, symbol)
                if key in transitions:
                    dest = transitions[key]
                    if isinstance(dest, str):
                        if dest != '-':
                            next_states.update(compute_epsilon_closure(dest, transitions))
                    elif isinstance(dest, list):
                        for d in dest:
                            if d != '-':
                                next_states.update(compute_epsilon_closure(d, transitions))

            next_states_frozen = frozenset(next_states)
            afd_transitions[(current_set, symbol)] = next_states_frozen
            if next_states_frozen not in visited:
                queue.append(next_states_frozen)

    return afd_transitions, afd_initial, afd_finals, afd_states

# Intentamos abrir el archivo, si no lo encuentra lanzamos una excepción.
try:
    with open(fileName, "r") as file:
        lines = file.readlines()
        # Leemos el alfabeto 
        states = readInfo( lines, 0 )
        # Leemos el estado inicial.
        initialState = lines[1].strip()
        # Leemos los estados finales como lista.
        finalStates = readInfo( lines, 2 )
        # Leemos el alphabeto del automata.
        alphabet = readInfo( lines, 3)
        alphabet.append('-')

        # Creamos un diccionario vacio.
        transitions = {}
        k = 0
        # Leeremos la función de transición.
        for line in lines[4:]:
            row = line.strip().split(" ") # [e0, e1, e2]
            origin = states[k] # e0
            i = 0
            for state in row:
                if( "," in state ):
                    state = state.split(",")
                    transitions[( origin, alphabet[i] )] = state
                else:    
                    transitions[( origin, alphabet[i] )] = state
                i = i + 1
            k = k + 1
        
        # Imprimimos tabla de transiciones.
        print("✅ Automata cargado.")
        print(f"Estados del automata: {states}")
        print(f"Estados finales: {finalStates}")
        print(f"Estado inicial: {initialState}")
        print(f"Alphabet: {alphabet}")
        for key, value in transitions.items():
            print(f"{key} -> {value}")

        print("\n🔁 Convirtiendo a AFD...\n")
        afd_transitions, afd_initial, afd_finals, afd_states = afn_to_afd_with_epsilon(transitions, alphabet, initialState, finalStates)

        print("✅ AFD generado con éxito.")
        print(f"Estados del AFD: {['{' + ','.join(s) + '}' for s in afd_states]}")
        print(f"Estado inicial del AFD: {{{','.join(afd_initial)}}}")
        print(f"Estados finales del AFD: {['{' + ','.join(s) + '}' for s in afd_finals]}")

        print("Transiciones del AFD:")
        for (state, symbol), dest in afd_transitions.items():
            print(f"{{{','.join(state)}}} --{symbol}--> {{{','.join(dest)}}}")
        # Dibujar autómata
        draw_automaton(afd_transitions, afd_initial, afd_finals) 

except FileNotFoundError:
    print(" X - Archivo no encontrado")
    exit(1)
except Exception:
    print(" X - Ocurrio un error inesperado.")
    exit(1)
    

def verifyInput(cadena):
    currentState = afd_initial  # Es un frozenset

    for symbol in cadena:
        # Verifica que el caracter pertenezca al alfabeto.
        if symbol not in alphabet:
            return False  
        key = (currentState, symbol)
        if key not in afd_transitions:
            return False
        currentState = afd_transitions[key]  # Usar afd_transitions, no transitions

    # Verifica si el estado actual (conjunto) está en los estados finales
    return currentState in afd_finals

# Comenzamos verificación de cadenas.
print(" * Ingrese cadenas para validar el automata. ")
cadena = ""
while ( cadena.upper() != "SALIR" ): 
    cadena = input()
    if( verifyInput(cadena) ):
        print(" ✅ - Cadena valida.")
    else:
        print(" ❌ - Cadena invalida.")
