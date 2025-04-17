# Debería funcionar en linux, sin embargo, no funciona en windows por problemas relacionados con el PATH

from graphviz import Digraph

dot = Digraph()
dot.node('A')
dot.node('B')
dot.edge('A', 'B')
dot.render('output_graph', view=True)
