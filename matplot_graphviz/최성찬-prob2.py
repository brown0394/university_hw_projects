


from graphviz import Digraph

s = Digraph('structs', filename='최성찬-prob2.gv', node_attr={'shape': 'record'})
s.format = 'png'
s.node('struct1', r'Zipeer |{ left | <lf>. } |{ focus | <fc>. }|{ right | 0 }| { top | ... }')
s.node('struct2', r'<list>List | <fst>. | <sec>. | <third>.')
s.node('struct3', r'<leaf>\<leaf\> |{ value | <val>.}')
s.node('struct4', r'\<fruit\>')
s.node('struct5', r'<leaf>\<leaf\> |{ value | <val>.}')
s.node('struct6', r'\"3\"')
s.node('struct7', r'\"2\"')
s.node('struct8', r'\<worm\>')

s.edges([('struct1:<lf>', 'struct2:list'), ('struct1:fc', 'struct8')])
s.edges([('struct2:fst', 'struct4:f0'), ('struct2:sec', 'struct3:leaf'), ('struct2:third', 'struct5:leaf')])
s.edges([('struct3:<val>', 'struct6:f0'), ('struct5:<val>', 'struct7:f0')])
s.view()

