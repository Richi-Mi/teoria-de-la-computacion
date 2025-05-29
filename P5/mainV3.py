import graphviz

class AFN:
    def __init__(self):
        self.estados = []
        self.alfabeto = []
        self.estado_inicial = ''
        self.estados_finales = []
        self.transiciones = {}

    def cargar_desde_archivo(self, archivo):
        with open(archivo, 'r') as f:
            lineas = [linea.strip() for linea in f.readlines() if linea.strip()]

        self.estados = lineas[0].split()
        self.estado_inicial = lineas[1]
        self.estados_finales = lineas[2].split()
        self.alfabeto = lineas[3].split() + ['ε']

        for i, estado in enumerate(self.estados):
            for j, simbolo in enumerate(self.alfabeto):
                destinos = lineas[4 + i].split()[j]
                if destinos != '-' and destinos:
                    clave = (estado, simbolo)
                    self.transiciones[clave] = destinos.split(',')

    def obtener_transiciones(self, estado, simbolo):
        return self.transiciones.get((estado, simbolo), [])

    def cerradura_epsilon(self, estados):
        stack = list(estados)
        resultado = set(estados)
        while stack:
            estado = stack.pop()
            for destino in self.obtener_transiciones(estado, 'ε'):
                if destino not in resultado and destino != '-':
                    resultado.add(destino)
                    stack.append(destino)
        return resultado


class AFD:
    def __init__(self):
        self.estados = []
        self.estado_inicial = ''
        self.estados_finales = []
        self.transiciones = {}
        self.nombres_estados = {}  # frozenset -> E1, E2...

    def agregar_transicion(self, desde, simbolo, hacia):
        self.transiciones[(desde, simbolo)] = hacia

    def generar_dot(self, nombre_archivo='automata'):
        dot = graphviz.Digraph(format='png')
        dot.attr(rankdir='LR', fontname='Helvetica')

        # Nodo invisible de inicio
        dot.node('', shape='none')

        for estado in self.estados:
            estilo = {
                "style": "filled",
                "fillcolor": "#1f77b4",  # Azul
                "fontcolor": "white",
                "fontname": "Helvetica"
            }
            forma = "doublecircle" if estado in self.estados_finales else "circle"
            dot.node(estado, shape=forma, **estilo)

        dot.edge('', self.estado_inicial, color="#006400")  # Verde oscuro

        for (desde, simbolo), hacia in self.transiciones.items():
            dot.edge(desde, hacia, label=simbolo, color="#006400", fontcolor="#006400", fontname="Helvetica")

        dot.render(nombre_archivo, cleanup=True)

    def exportar_a_txt(self, nombre_archivo, alfabeto):
        with open(nombre_archivo, 'w') as f:
            f.write(" ".join(self.estados) + "\n")
            f.write(self.estado_inicial + "\n")
            f.write(" ".join(self.estados_finales) + "\n")
            f.write(" ".join(alfabeto) + "\n")
            for estado in self.estados:
                linea = []
                for simbolo in alfabeto:
                    destino = self.transiciones.get((estado, simbolo), '-')
                    linea.append(destino)
                f.write(" ".join(linea) + "\n")


def convertir_a_afd(afn):
    afd = AFD()
    alfabeto = [s for s in afn.alfabeto if s != 'ε']
    estado_inicial = frozenset(afn.cerradura_epsilon([afn.estado_inicial]))

    contador = [1]
    def nombre_estado(conjunto):
        if conjunto not in afd.nombres_estados:
            afd.nombres_estados[conjunto] = f"E{contador[0]}"
            contador[0] += 1
        return afd.nombres_estados[conjunto]

    estados_afn_a_afd = {estado_inicial: nombre_estado(estado_inicial)}
    pendientes = [estado_inicial]

    afd.estado_inicial = estados_afn_a_afd[estado_inicial]
    afd.estados.append(afd.estado_inicial)

    while pendientes:
        actual = pendientes.pop()
        nombre_actual = estados_afn_a_afd[actual]

        for simbolo in alfabeto:
            destinos = set()
            for estado in actual:
                for trans in afn.obtener_transiciones(estado, simbolo):
                    if trans != '-':
                        destinos.update(afn.cerradura_epsilon([trans]))

            if not destinos:
                continue

            destinos_frozenset = frozenset(destinos)
            if destinos_frozenset not in estados_afn_a_afd:
                nombre_destino = nombre_estado(destinos_frozenset)
                estados_afn_a_afd[destinos_frozenset] = nombre_destino
                afd.estados.append(nombre_destino)
                pendientes.append(destinos_frozenset)

            afd.agregar_transicion(nombre_actual, simbolo, estados_afn_a_afd[destinos_frozenset])

    for conjunto_estados, nombre in estados_afn_a_afd.items():
        if any(e in afn.estados_finales for e in conjunto_estados):
            afd.estados_finales.append(nombre)

    return afd


def main():
    archivo = input("Ingresa archivo donde está el autómata:\n").strip()
    afn = AFN()
    afn.cargar_desde_archivo(archivo)
    print("✅ Autómata cargado.")

    print("Estados del autómata:", afn.estados)
    print("Estados finales:", afn.estados_finales)
    print("Estado inicial:", afn.estado_inicial)
    print("Alfabeto:", afn.alfabeto)

    for (estado, simbolo), destinos in afn.transiciones.items():
        print(f"({estado}, {simbolo}) -> {destinos}")

    print("\n🔁 Convirtiendo a AFD...\n")
    afd = convertir_a_afd(afn)
    print("✅ AFD generado con éxito.")
    print("Estados del AFD:", afd.estados)
    print("Estado inicial del AFD:", afd.estado_inicial)
    print("Estados finales del AFD:", afd.estados_finales)
    print("Transiciones del AFD:")
    for (desde, simbolo), hacia in afd.transiciones.items():
        print(f"{desde} --{simbolo}--> {hacia}")

    afd.generar_dot()
    print("✅ Imagen del autómata generada como 'automata.png'")

    afd.exportar_a_txt("AFD_generado.txt", [s for s in afn.alfabeto if s != 'ε'])
    print("✅ Archivo 'AFD_generado.txt' generado con la descripción del AFD.")
    print(" * Ingresa cadenas para validar el autómata. Escribe 'SALIR' para terminar.")

    alfabeto_sin_epsilon = [s for s in afn.alfabeto if s != 'ε']

    while True:
        cadena = input(">> ").strip()
        if cadena.upper() == "SALIR":
            print("Saliendo.")
            break

        estado_actual = afd.estado_inicial
        recorrido = [estado_actual]
        valida = True

        for simbolo in cadena:
            if simbolo not in alfabeto_sin_epsilon:
                print(f"❌ Símbolo inválido: '{simbolo}' no está en el alfabeto.")
                valida = False
                break
            estado_siguiente = afd.transiciones.get((estado_actual, simbolo))
            if not estado_siguiente:
                print(f"❌ No hay transición desde {estado_actual} con '{simbolo}'")
                valida = False
                break
            recorrido.append(estado_siguiente)
            estado_actual = estado_siguiente

        if valida:
            print("🔄 Recorrido:", " -> ".join(recorrido))
            if estado_actual in afd.estados_finales:
                print("✅ Cadena ACEPTADA.")
            else:
                print("❌ Cadena RECHAZADA. Estado final no es de aceptación.")


if __name__ == "__main__":
    main()
