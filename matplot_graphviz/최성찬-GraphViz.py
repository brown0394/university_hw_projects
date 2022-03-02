import graphviz as gv

tmp="""
graph {
    rankdir=LR;
    c[fillcolor="blue" style=filled color="black" fontcolor="black"]
    a -- { b c }; b -- { c d }; c -- { d e f }; d -- { e }; e -- f;

    { rank=same; b, c }
    { rank=same; d, e, f }
}
"""
s = gv.Source(tmp, filename="Figures\mostconstraining", format="png")
s.view()

tmp="""
graph {
    rankdir=LR;
    b[fillcolor="green" style=filled color="black" fontcolor="black"]
    c[fillcolor="blue" style=filled color="black" fontcolor="black"]
    e[fillcolor="green" style=filled color="black" fontcolor="black"]
    a -- { b c }; b -- { c d }; c -- { d e f }; d -- { e }; e -- f;

    { rank=same; b, c }
    { rank=same; d, e, f }
}
"""
s = gv.Source(tmp, filename="Figures\mostconstraining2", format="png")
s.view()

tmp="""
graph {
    rankdir=LR;
    a[fillcolor="red" style=filled color="black" fontcolor="black"]
    b[fillcolor="green" style=filled color="black" fontcolor="black"]
    c[fillcolor="blue" style=filled color="black" fontcolor="black"]
    d[fillcolor="red" style=filled color="black" fontcolor="black"]
    e[fillcolor="green" style=filled color="black" fontcolor="black"]
    f[fillcolor="red" style=filled color="black" fontcolor="black"]
    a -- { b c }; b -- { c d }; c -- { d e f }; d -- { e }; e -- f;

    { rank=same; b, c }
    { rank=same; d, e, f }
}
"""
s = gv.Source(tmp, filename="Figures\mostconstraining3", format="png")
s.view()

tmp="""
graph {
    rankdir=LR;
    a[fillcolor="red" style=filled color="black" fontcolor="black"]
    b[fillcolor="green" style=filled color="black" fontcolor="black"]
    d[fillcolor="red" style=filled color="black" fontcolor="black"]
    a -- { b "{blue}" }; b -- { "{blue}" d }; "{blue}" -- { d "{blue, green}" f };
    d -- { "{blue, green}" }; "{blue, green}" -- f;

    { rank=same; b, "{blue}" }
    { rank=same; d, "{blue, green}", f }
}
"""
s = gv.Source(tmp, filename="Figures\leastconstraining", format="png")
s.view()

tmp="""
graph {
    rankdir=LR;
    a[fillcolor="red" style=filled color="black" fontcolor="black"]
    b[fillcolor="green" style=filled color="black" fontcolor="black"]
    d[fillcolor="blue" style=filled color="black" fontcolor="black"]
    a -- { b "{ }" }; b -- { "{ }" d }; "{ }" -- { d "{red, green}" f };
    d -- { "{red, green}" }; "{red, green}" -- f;

    { rank=same; b, "{ }" }
    { rank=same; d, "{red, green}", f }
}
"""
s = gv.Source(tmp, filename="Figures\leastconstraining2", format="png")
s.view()

tmp="""
graph {
    rankdir=LR;
    a[fillcolor="red" style=filled color="black" fontcolor="black"]
    b[fillcolor="green" style=filled color="black" fontcolor="black"]
    d[fillcolor="red" style=filled color="black" fontcolor="black"]
    f[fillcolor="red" style=filled color="black" fontcolor="black"]
    a -- { b "{blue}" }; b -- { "{blue}" d }; "{blue}" -- { d "{blue, green}" f };
    d -- { "{blue, green}" }; "{blue, green}" -- f;

    { rank=same; b, "{blue}" }
    { rank=same; d, "{blue, green}", f }
}
"""
s = gv.Source(tmp, filename="Figures\leastconstraining3", format="png")
s.view()

tmp="""
graph {
    rankdir=LR;
    a[fillcolor="red" style=filled color="black" fontcolor="black"]
    b[fillcolor="green" style=filled color="black" fontcolor="black"]
    a -- { b "{blue}" }; b -- { "{blue}" "{blue, red}" }; "{blue}" -- { "{blue, red}" e f };
    "{blue, red}" -- { e }; e -- f;

    { rank=same; b, "{blue}" }
    { rank=same; "{blue, red}", e, f }
}
"""
s = gv.Source(tmp, filename="Figures\mostconstrained", format="png")
s.view()

tmp="""
graph {
    rankdir=LR;
    a[fillcolor="red" style=filled color="black" fontcolor="black"]
    b[fillcolor="green" style=filled color="black" fontcolor="black"]
    c[fillcolor="blue" style=filled color="black" fontcolor="black"]
    a -- { b c }; b -- { c "{red}" }; c -- { "{red}" e f };
    "{red}" -- { e }; e -- f;

    { rank=same; b, c }
    { rank=same; "{red}", e, f }
}
"""
s = gv.Source(tmp, filename="Figures\mostconstrained2", format="png")
s.view()

tmp="""
graph {
    rankdir=LR;
    a[fillcolor="red" style=filled color="black" fontcolor="black"]
    b[fillcolor="green" style=filled color="black" fontcolor="black"]
    c[fillcolor="blue" style=filled color="black" fontcolor="black"]
    d[fillcolor="red" style=filled color="black" fontcolor="black"]
    a -- { b c }; b -- { c d }; c -- { d "{green}" "{red}" };
    d -- { "{green}" }; "{green}" -- "{red}";

    { rank=same; b, c }
    { rank=same; d, "{green}", "{red}" }
}
"""
s = gv.Source(tmp, filename="Figures\mostconstrained3", format="png")
s.view()