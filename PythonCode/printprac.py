line = line.split(input())
newline = ""
linelist = []
length = 0
count = 0
last = 0
length = len(line)

while count < length:
    if len(line[count]) > 4:       
        linelist = list(line[count])
        linelist[0] = linelist[0].upper()
        newline += "".join(linelist)
    else:
        newline += line[count]     
    count += 1
    if count != length:
        newline += " "

print(newline)
