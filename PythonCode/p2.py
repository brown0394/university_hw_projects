line = "Yo~ Happy Python"
ustr = line.upper()
plist = []
for c in ustr:
    n = ustr.count(c)
    if c.isalpha():
        plist.append((n, c))
print(plist)
plist.sort()
plist.reverse()
maxcnt = plist[0][0]
mclist = []
for p in plist:
    cnt = p[0]
    if cnt == maxcnt:
        mclist.append(p[1])
print(mclist)
mclist.sort()
print(mclist)
print(mclist[0])
