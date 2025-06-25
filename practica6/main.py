import re
from typing import Dict, List, Set, Tuple

class GrammarParser:
    def __init__(self):
        self.productions = {}  # Dict[str, List[List[str]]]
        self.terminals = set()
        self.non_terminals = set()
        self.start_symbol = None
    
    def load_from_file(self, filename: str):
        """Carga la gramática desde un archivo de texto"""
        with open(filename, 'r', encoding='utf-8') as file:
            lines = file.readlines()
        
        for line in lines:
            line = line.strip()
            if not line or line.startswith('#'):  # Ignorar líneas vacías y comentarios
                continue
            
            self.parse_production(line)
        
        self._identify_symbols()
        if not self.start_symbol:
            # El primer símbolo no terminal encontrado es el inicial
            self.start_symbol = next(iter(self.productions.keys()))
    
    def parse_production(self, line: str):
        """Parsea una línea de producción: <A> := alpha | beta"""
        # Dividir por :=
        parts = line.split(':=')
        if len(parts) != 2:
            raise ValueError(f"Formato inválido: {line}")
        
        left_side = parts[0].strip()
        right_side = parts[1].strip()
        
        # Extraer símbolo no terminal del lado izquierdo
        match = re.match(r'<(\w+)>', left_side)
        if not match:
            raise ValueError(f"Símbolo no terminal inválido: {left_side}")
        
        non_terminal = match.group(1)
        
        # Dividir producciones por |
        productions = right_side.split('|')
        
        if non_terminal not in self.productions:
            self.productions[non_terminal] = []
        
        for production in productions:
            production = production.strip()
            parsed_production = self._parse_right_side(production)
            self.productions[non_terminal].append(parsed_production)
    
    def _parse_right_side(self, production: str) -> List[str]:
        """Parsea el lado derecho de una producción"""
        if production == 'λ' or production == 'lambda':
            return ['λ']
        
        tokens = []
        i = 0
        while i < len(production):
            if production[i] == '<':
                # Encontrar el símbolo no terminal completo
                end = production.find('>', i)
                if end == -1:
                    raise ValueError(f"Símbolo no terminal mal formateado: {production}")
                tokens.append(production[i:end+1])
                i = end + 1
            elif production[i].isspace():
                i += 1
            else:
                # Símbolo terminal
                tokens.append(production[i])
                i += 1
        
        return tokens
    
    def _identify_symbols(self):
        """Identifica símbolos terminales y no terminales"""
        self.non_terminals = set(self.productions.keys())
        
        for productions_list in self.productions.values():
            for production in productions_list:
                for symbol in production:
                    if symbol.startswith('<') and symbol.endswith('>'):
                        # Es un no terminal
                        nt = symbol[1:-1]
                        self.non_terminals.add(nt)
                    elif symbol != 'λ':
                        # Es un terminal
                        self.terminals.add(symbol)
    
    def print_grammar(self):
        """Imprime la gramática de forma legible"""
        print("=== GRAMÁTICA ===")
        print(f"Símbolo inicial: <{self.start_symbol}>")
        print(f"No terminales: {{{', '.join(sorted(self.non_terminals))}}}")
        print(f"Terminales: {{{', '.join(sorted(self.terminals))}}}")
        print("\nProducciones:")
        
        for nt in sorted(self.productions.keys()):
            productions_str = []
            for prod in self.productions[nt]:
                prod_str = ''.join(prod) if prod != ['λ'] else 'λ'
                productions_str.append(prod_str)
            print(f"  <{nt}> := {' | '.join(productions_str)}")
    
    # ===== ALGORITMOS DE LIMPIEZA =====
    
    def remove_non_generative(self):
        """Elimina símbolos no generativos (que no generan cadenas de terminales)"""
        print("\n=== ELIMINANDO SÍMBOLOS NO GENERATIVOS ===")
        
        generative = set()
        changed = True
        
        while changed:
            changed = False
            for nt, productions_list in self.productions.items():
                if nt in generative:
                    continue
                
                for production in productions_list:
                    if self._is_generative(production, generative):
                        generative.add(nt)
                        changed = True
                        print(f"  <{nt}> es generativo")
                        break
        
        # Eliminar símbolos no generativos
        non_generative = self.non_terminals - generative
        if non_generative:
            print(f"Símbolos no generativos encontrados: {non_generative}")
            self._remove_symbols(non_generative)
        else:
            print("No se encontraron símbolos no generativos")
        
        # PASO ADICIONAL: Eliminar producciones vacías (λ)
        self.remove_empty_productions()
    
    def _is_generative(self, production: List[str], generative: Set[str]) -> bool:
        """Verifica si una producción es generativa"""
        if production == ['λ']:
            return True
        
        for symbol in production:
            if symbol.startswith('<') and symbol.endswith('>'):
                nt = symbol[1:-1]
                if nt not in generative:
                    return False
            # Los terminales siempre son generativos
        
        return True
    
    def remove_unreachable(self):
        """Elimina símbolos inaccesibles desde el símbolo inicial"""
        print("\n=== ELIMINANDO SÍMBOLOS INACCESIBLES ===")
        
        reachable = set()
        queue = [self.start_symbol]
        reachable.add(self.start_symbol)
        
        while queue:
            current = queue.pop(0)
            if current in self.productions:
                for production in self.productions[current]:
                    for symbol in production:
                        if symbol.startswith('<') and symbol.endswith('>'):
                            nt = symbol[1:-1]
                            if nt not in reachable:
                                reachable.add(nt)
                                queue.append(nt)
                                print(f"  <{nt}> es accesible desde <{current}>")
        
        # Eliminar símbolos inaccesibles
        unreachable = self.non_terminals - reachable
        if unreachable:
            print(f"Símbolos inaccesibles encontrados: {unreachable}")
            self._remove_symbols(unreachable)
        else:
            print("No se encontraron símbolos inaccesibles")
    
    def remove_unit_productions(self):
        """Elimina producciones unitarias (A -> B)"""
        print("\n=== ELIMINANDO PRODUCCIONES UNITARIAS ===")
        
        # Encontrar todas las producciones unitarias
        unit_pairs = []
        for nt, productions_list in self.productions.items():
            for production in productions_list:
                if (len(production) == 1 and 
                    production[0].startswith('<') and 
                    production[0].endswith('>')):
                    target = production[0][1:-1]
                    unit_pairs.append((nt, target))
                    print(f"  Producción unitaria: <{nt}> -> <{target}>")
        
        if not unit_pairs:
            print("No se encontraron producciones unitarias")
            return
        
        # Calcular clausura transitiva de pares unitarios
        unit_closure = {}
        for nt in self.non_terminals:
            unit_closure[nt] = self._unit_closure(nt, unit_pairs)
        
        # Crear nuevas producciones
        new_productions = {}
        for nt in self.productions:
            new_productions[nt] = []
            
            # Agregar producciones no unitarias originales
            for production in self.productions[nt]:
                if not (len(production) == 1 and 
                       production[0].startswith('<') and 
                       production[0].endswith('>')):
                    new_productions[nt].append(production)
            
            # Agregar producciones derivadas de la clausura unitaria
            for target in unit_closure[nt]:
                if target in self.productions:
                    for production in self.productions[target]:
                        if not (len(production) == 1 and 
                               production[0].startswith('<') and 
                               production[0].endswith('>')):
                            new_productions[nt].append(production)
        
        self.productions = new_productions
        print("Producciones unitarias eliminadas")
    
    def _unit_closure(self, nt: str, unit_pairs: List[Tuple[str, str]]) -> Set[str]:
        """Calcula la clausura transitiva de producciones unitarias"""
        closure = {nt}
        changed = True
        
        while changed:
            changed = False
            for src, target in unit_pairs:
                if src in closure and target not in closure:
                    closure.add(target)
                    changed = True
        
        closure.remove(nt)  # Remover el símbolo original
        return closure
    
    def remove_useless_symbols(self):
        """Elimina símbolos inútiles (no generativos + inaccesibles)"""
        print("\n=== LIMPIEZA COMPLETA DE SÍMBOLOS INÚTILES ===")
        original_count = len(self.non_terminals)
        
        # Primero eliminar no generativos, luego inaccesibles
        self.remove_non_generative()
        self.remove_unreachable()
        
        final_count = len(self.non_terminals)
        print(f"Símbolos eliminados: {original_count - final_count}")
    
    def _remove_symbols(self, symbols_to_remove: Set[str]):
        """Elimina símbolos de la gramática"""
        # Eliminar producciones de estos símbolos
        for symbol in symbols_to_remove:
            if symbol in self.productions:
                del self.productions[symbol]
        
        # Eliminar apariciones en el lado derecho
        for nt in list(self.productions.keys()):
            new_productions = []
            for production in self.productions[nt]:
                # Verificar si la producción contiene símbolos eliminados
                contains_removed = False
                for symbol in production:
                    if symbol.startswith('<') and symbol.endswith('>'):
                        if symbol[1:-1] in symbols_to_remove:
                            contains_removed = True
                            break
                
                if not contains_removed:
                    new_productions.append(production)
            
            self.productions[nt] = new_productions
        
        # Actualizar conjuntos de símbolos
        self.non_terminals -= symbols_to_remove
    
    def remove_empty_productions(self):
        """Elimina producciones vacías (λ-producciones)"""
        print("\n=== ELIMINANDO PRODUCCIONES VACÍAS ===")
        
        # Paso 1: Encontrar símbolos que pueden derivar λ
        nullable = set()
        changed = True
        
        while changed:
            changed = False
            for nt, productions_list in self.productions.items():
                if nt in nullable:
                    continue
                
                for production in productions_list:
                    if production == ['λ']:
                        nullable.add(nt)
                        changed = True
                        print(f"  <{nt}> puede derivar λ (producción directa)")
                        break
                    elif self._all_nullable(production, nullable):
                        nullable.add(nt)
                        changed = True
                        print(f"  <{nt}> puede derivar λ (producción: {' '.join(production)})")
                        break
        
        # Paso 2: Generar nuevas producciones sin λ
        new_productions = {}
        
        for nt, productions_list in self.productions.items():
            new_productions[nt] = []
            
            for production in productions_list:
                if production == ['λ']:
                    # Solo mantener λ si es del símbolo inicial y es necesario
                    if nt == self.start_symbol:
                        # Verificar si el símbolo inicial necesita generar λ
                        has_non_lambda = any(prod != ['λ'] for prod in productions_list)
                        if not has_non_lambda:
                            new_productions[nt].append(['λ'])
                    continue
                
                # Generar todas las combinaciones sin símbolos que pueden ser λ
                combinations = self._generate_combinations(production, nullable)
                for combo in combinations:
                    if combo and combo not in new_productions[nt]:  # No agregar producciones vacías
                        new_productions[nt].append(combo)
        
        # Eliminar símbolos que solo tenían producciones λ
        empty_symbols = []
        for nt in list(new_productions.keys()):
            if not new_productions[nt]:  # No tiene producciones
                empty_symbols.append(nt)
                del new_productions[nt]
        
        if empty_symbols:
            print(f"Símbolos eliminados (solo tenían λ): {empty_symbols}")
        
        self.productions = new_productions
        self._identify_symbols()  # Actualizar conjuntos de símbolos
        
        print("Producciones vacías eliminadas")
    
    def _all_nullable(self, production: List[str], nullable: Set[str]) -> bool:
        """Verifica si todos los símbolos de una producción pueden derivar λ"""
        for symbol in production:
            if symbol.startswith('<') and symbol.endswith('>'):
                nt = symbol[1:-1]
                if nt not in nullable:
                    return False
            else:
                # Es un terminal, no puede ser λ
                return False
        return True
    
    def _generate_combinations(self, production: List[str], nullable: Set[str]) -> List[List[str]]:
        """Genera todas las combinaciones posibles eliminando símbolos nullable"""
        if not production:
            return [[]]
        
        result = []
        first = production[0]
        rest_combinations = self._generate_combinations(production[1:], nullable)
        
        # Agregar combinaciones que incluyen el primer símbolo
        for combo in rest_combinations:
            result.append([first] + combo)
        
        # Si el primer símbolo puede ser λ, agregar combinaciones sin él
        if (first.startswith('<') and first.endswith('>') and 
            first[1:-1] in nullable):
            for combo in rest_combinations:
                if combo:  # Solo agregar si no es vacía
                    result.append(combo)
        
        return result
    
    def clean_grammar(self):
        """Aplica todos los algoritmos de limpieza en orden"""
        print("=== INICIANDO LIMPIEZA COMPLETA DE GRAMÁTICA ===")
        self.print_grammar()
        
        # Orden correcto: producciones vacías -> unitarias -> no generativos -> inaccesibles
        self.remove_empty_productions()
        self.remove_unit_productions()
        self.remove_useless_symbols()
        
        print("\n=== GRAMÁTICA LIMPIA ===")
        self.print_grammar()
    
    def classify_grammar(self):
        """Clasifica la gramática según la jerarquía de Chomsky"""
        print("\n=== CLASIFICACIÓN DE GRAMÁTICA ===")
        
        # Verificar en orden: Tipo 3 -> Tipo 2 -> Tipo 1 -> Tipo 0
        if self._is_type3():
            print("🔸 TIPO 3 - Gramática Regular")
            return 3
        elif self._is_type2():
            print("🔸 TIPO 2 - Gramática Libre de Contexto")
            return 2
        elif self._is_type1():
            print("🔸 TIPO 1 - Gramática Sensible al Contexto")
            return 1
        else:
            print("🔸 TIPO 0 - Gramática Sin Restricciones")
            return 0
    
    def _is_type3(self):
        """Verifica si es Tipo 3 (Regular)"""
        print("  Verificando Tipo 3 (Regular)...")
        
        for nt, productions_list in self.productions.items():
            for production in productions_list:
                if production == ['λ']:
                    continue
                
                # Verificar formato: A -> a | aB | a (lineal derecha)
                # o A -> a | Ba | a (lineal izquierda)
                if not self._is_regular_production(production):
                    print(f"    ❌ <{nt}> := {''.join(production)} no es regular")
                    return False
        
        print("    ✅ Todas las producciones son regulares")
        return True
    
    def _is_regular_production(self, production):
        """Verifica si una producción es regular"""
        if len(production) == 1:
            # A -> a (terminal)
            return production[0] in self.terminals
        elif len(production) == 2:
            # A -> aB (lineal derecha) o A -> Ba (lineal izquierda)
            first, second = production[0], production[1]
            
            # Lineal derecha: terminal + no terminal
            if (first in self.terminals and 
                second.startswith('<') and second.endswith('>')):
                return True
            
            # Lineal izquierda: no terminal + terminal
            if (first.startswith('<') and first.endswith('>') and 
                second in self.terminals):
                return True
        
        return False
    
    def _is_type2(self):
        """Verifica si es Tipo 2 (Libre de Contexto)"""
        print("  Verificando Tipo 2 (Libre de Contexto)...")
        
        for nt, productions_list in self.productions.items():
            # Verificar que el lado izquierdo sea un solo no terminal
            # (esto ya está garantizado por nuestro parser, pero lo verificamos)
            if len(nt) == 0:
                print(f"    ❌ Lado izquierdo vacío")
                return False
            
            # En gramáticas libres de contexto, lado izquierdo = un no terminal
            # lado derecho = cualquier cadena de terminales y no terminales
            for production in productions_list:
                # Cualquier producción es válida en gramáticas libres de contexto
                # siempre que el lado izquierdo sea un solo no terminal
                pass
        
        print("    ✅ Es libre de contexto (lado izquierdo = un no terminal)")
        return True
    
    def _is_type1(self):
        """Verifica si es Tipo 1 (Sensible al Contexto)"""
        print("  Verificando Tipo 1 (Sensible al Contexto)...")
        
        for nt, productions_list in self.productions.items():
            for production in productions_list:
                if production == ['λ']:
                    # λ-producciones solo permitidas en símbolo inicial
                    # si no aparece en lado derecho
                    if nt != self.start_symbol or self._appears_in_right_side(nt):
                        print(f"    ❌ λ-producción inválida en <{nt}>")
                        return False
                    continue
                
                # Verificar restricción de longitud: |α| ≤ |β|
                # En nuestro caso simplificado: lado izquierdo ≤ lado derecho
                left_length = 1  # Un no terminal
                right_length = len(production)
                
                if left_length > right_length:
                    print(f"    ❌ Violación de longitud: <{nt}> := {''.join(production)}")
                    return False
        
        print("    ✅ Cumple restricciones de longitud")
        return True
    
    def _appears_in_right_side(self, symbol):
        """Verifica si un símbolo aparece en el lado derecho de alguna producción"""
        target = f"<{symbol}>"
        for productions_list in self.productions.values():
            for production in productions_list:
                if target in production:
                    return True
        return False
    
    def detailed_analysis(self):
        """Análisis detallado de la gramática"""
        print("\n=== ANÁLISIS DETALLADO ===")
        
        # Información básica
        print(f"Símbolo inicial: <{self.start_symbol}>")
        print(f"No terminales ({len(self.non_terminals)}): {{{', '.join(sorted(self.non_terminals))}}}")
        print(f"Terminales ({len(self.terminals)}): {{{', '.join(sorted(self.terminals))}}}")
        print(f"Total de producciones: {sum(len(prods) for prods in self.productions.values())}")
        
        # Análisis de producciones
        lambda_prods = 0
        unit_prods = 0
        
        for nt, productions_list in self.productions.items():
            for production in productions_list:
                if production == ['λ']:
                    lambda_prods += 1
                elif (len(production) == 1 and 
                      production[0].startswith('<') and 
                      production[0].endswith('>')):
                    unit_prods += 1
        
        print(f"Producciones λ: {lambda_prods}")
        print(f"Producciones unitarias: {unit_prods}")
        
        # Clasificación
        grammar_type = self.classify_grammar()
        
        return grammar_type

if __name__ == "__main__":    
    # Cargar y procesar gramática
    parser = GrammarParser()
    parser.load_from_file('example.txt')
    parser.classify_grammar()
    
    # Aplicar limpieza completa
    parser.clean_grammar()