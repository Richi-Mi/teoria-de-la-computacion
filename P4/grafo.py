
# Funciona, pero se debe de forsar a usar la carpeta bin de Graphviz ya que no la encuentra

import os
from graphviz import Digraph

# AÑADE ESTA LÍNEA SI EL PATH NO FUNCIONA
os.environ["PATH"] += os.pathsep + r"C:\Program Files\Graphviz\bin"

dot = Digraph()
dot.node('A')
dot.node('B')
dot.edge('A', 'B')
dot.render('output_graph', view=True)
