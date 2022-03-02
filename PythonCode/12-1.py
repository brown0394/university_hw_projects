##ns = list(range(1,7))
####print (ns)
####print(list(range(0,6,3)))
####print(ns[0:0+3])
##
##m = [ns[n:n+3] for n in range(0,6,3)]
##print(m)
##
##def pr_mat(m):
##    for row in m:
##        rowst = [str(e) for e in row]
##        print(" ".join(rowst))
##pr_mat(m)


class Matrix:
    'simple class'
    def __init__(self, rows):##constructor
        self.rows = list(rows)
    def pr_mat(self):
        for row in self.rows:
            rowst = [str(e) for e in row]
            print(" ".join(rowst))
    def __str__(self):
        rowstrs = []
        for row in self.rows:
            rowst = [str(e) for e in row]
            rowstrs.append(" ".join(rowst))
        return "\n".join(rowstrs)##for to do print(m)
    def __repr__(self):
        return f"Matrix({self.rows})"
    def __getitem__(self, i):
        return self.rows[i]
    def __setitem__(self, i, newval):
        self.rows[i] = newval
            
ns = list(range(1,9))
ms = [ns[n:n+4] for n in range(0,9,4)]

m = Matrix(ms)
m.pr_mat()
print(m)


print(m[0])

m[0] = [9, 8, 7]

print(m)


