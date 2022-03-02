line = "Yo~ Happy Python"
ustr = line.upper()
cdict = {}
for c in ustr: 
    if c.isalpha():
         n = ustr.count(c)
         cdict[c] = n
maxcnt = max(cdict.values())
print(cdict)
for c in sorted(cdict.keys()):
    if cdict[c] == maxcnt:
        print(c)
        break
