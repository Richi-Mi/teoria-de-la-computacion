# Pedimos el nombre del archivo donde definimos el automata.
print("Ingresa archivo donde esta el automata: ")
fileName = input()

def readInfo( list, index ):
    # Regresamos la información como lista.
    return list[index].strip().split(" ")

# Intentamos abrir el archivo, si no lo encuentra lanzamos una excepción.
try:
    with open(fileName, "r") as file:
        lines = file.readlines()
        # Leemos el alfabeto 
        alphabet = readInfo( lines, 0 )
        # Leemos el numero de estados del automata.
        states   = lines[1].strip();
        # Leemos el estado inicial.
        initialState = lines[2].strip();
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
except FileNotFoundError:
    print(" X - Archivo no encontrado")
except Exception:
    print(" X - Ocurrio un error inesperado.")

def verifyInput(cadena):
    currentState = initialState      

    for symbol in cadena:
        # Verifica que el caracter pertenezca al alfabeto.
        if symbol not in alphabet:
            return False  
        # Creamos la tupla que servira para acceder al siguiente estado en el diccionario
        key = (currentState, symbol)
        # Verificamos que la tupla exista en el diccionario.
        if key not in transitions:
            return False
        currentState = transitions[key]
    
    # Verificamos que la cadena se encuentre en los estados finales.
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
    