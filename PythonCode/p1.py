line = "Yo~ Happy Python"
ustr = line.upper()
count = []
for c in ustr:
    if c.isalpha():
        count.append(ustr.count(c))
    else:
        count.append(-1)
maxcnt = max(count)
mclist = []
i = 0
for cnt in count:
    if cnt == maxcnt:
        mclist.append(ustr[i])
    i += 1
print(mclist)
mclist.sort()
print(mclist)
print(mclist[0])
