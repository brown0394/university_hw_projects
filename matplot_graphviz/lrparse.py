
# See this site https://www.tonyballantyne.com/graphs.html


from graphviz import Source

dot_str = """
digraph D {
  rankdir=LR;
  I0 [label="I0\nS\' -> .S\nS -> .Vd\nS -> .VcE\nV -> .a"]
  I1 [label="I1\nS\' -> S."]
  I2 [label="I2\nS -> V.d\nS -> V.cE"]
  I3 [label="I3\nV -> a."]
  I4 [label="I4\nS -> Vd."]
  I5 [label="I5\nS -> Vc.E\nE -> .V\nE -> .b\nV -> .a"]
  I6 [label="I6\nS -> VcE."]
  I7 [label="I7\nE -> V."]
  I8 [label="I8\nE -> b."]
  I0 -> I1 [label = "S"]
  I0 -> I2 [label = "V"]
  I2 -> I4 [label = "d"]
  I2 -> I5 [label = "c"]
  I5 -> I6 [label = "E"]
  I5 -> I7 [label = "V"]
  I5 -> I8 [label = "b"]
  I5 -> I3 [label = "a"]
  I0 -> I3 [label = "a"]
}
"""
s = Source( dot_str, filename="lrparse.gv", format="png")
s.view()





