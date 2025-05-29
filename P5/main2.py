import graphviz

class AFN:
    def __init__(self):
        self.estados = []
        self.alfabeto = []
        self.estado_inicial = ''
        self.estados_finales = []
        self.transiciones = {}  # (estado, simbolo): [estados]

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
        self.transiciones = {}  # (estado, simbolo): estado

    def agregar_transicion(self, desde, simbolo, hacia):
        self.transiciones[(desde, simbolo)] = hacia

    def generar_dot(self, nombre_archivo='automata.png'):
        dot = graphviz.Digraph(format='png')
        dot.attr(rankdir='LR')

        dot.node('', shape='none')
        for estado in self.estados:
            if estado in self.estados_finales:
                dot.node(estado, shape='doublecircle')
            else:
                dot.node(estado)

        dot.edge('', self.estado_inicial)

        for (desde, simbolo), hacia in self.transiciones.items():
            dot.edge(desde, hacia, label=simbolo)

        dot.render(nombre_archivo, cleanup=True)


def convertir_a_afd(afn):
    afd = AFD()
    alfabeto = [s for s in afn.alfabeto if s != 'ε']

    estado_inicial = frozenset(afn.cerradura_epsilon([afn.estado_inicial]))
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


def nombre_estado(conjunto_estados):
    if not conjunto_estados:
        return None
    return "{" + ",".join(sorted(conjunto_estados)) + "}"


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
    print(" * Ingresa cadenas para validar el autómata. Escribe 'SALIR' para terminar.")


if __name__ == "__main__":
    main()
