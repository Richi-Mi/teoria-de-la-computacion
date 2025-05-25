from graphviz import Digraph

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

    # Renderizar
    dot.render('automata', format='png', cleanup=True)
    print("✅ Imagen del autómata generada como 'automata.png'")

# Intentamos abrir el archivo, si no lo encuentra lanzamos una excepción.
try:
    with open(fileName, "r") as file:
        lines = file.readlines()
        # Leemos el alfabeto 
        alphabet = readInfo( lines, 0 )
        # Leemos el numero de estados del automata.
        states   = lines[1].strip()
        # Leemos el estado inicial.
        initialState = lines[2].strip()
        # Leemos los estados finales como lista.
        finalStates = readInfo( lines, 3 )

        # Creamos un diccionario vacio.
        transitions = {}

        # Leeremos la función de transición.
        for line in lines[4:]:
            fun = line.strip().split(" ") 
            originWithSimbol = fun[0].split(",")
            origin = originWithSimbol[0]
            simbol = originWithSimbol[1]
            transitions[(origin, simbol)] = fun[1]
        
        # Imprimimos tabla de transiciones.
        print(" * Automata cargado. ")
        for key, value in transitions.items():
           print(f"{key} -> {value}")

        # Dibujar autómata
        draw_automaton(transitions, initialState, finalStates)

except FileNotFoundError:
    print(" X - Archivo no encontrado")
    exit(1)
except Exception:
    print(" X - Ocurrio un error inesperado.")
    exit(1)
    

def verifyInput(cadena):
    currentState = initialState      

    for symbol in cadena:
        # Verifica que el caracter pertenezca al alfabeto.
        if symbol not in alphabet:
            return False  
        key = (currentState, symbol)
        if key not in transitions:
            return False
        currentState = transitions[key]
    
    if currentState in finalStates:
        return True
    else:
        return False

# Comenzamos verificación de cadenas.
print(" * Ingrese cadenas para validar el automata. ")
cadena = ""
while ( cadena.upper() != "SALIR" ): 
    cadena = input()
    if( verifyInput(cadena) ):
        print(" 0 - CADENA VALIDA. ")
    else:
        print(" X - Cadena invalida. ")
