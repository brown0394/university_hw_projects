#coding : utf-8

def median(s1, s2):
    i = 0
    medianstr = str()
    first = True
    while i < len(s1) and i < len(s2):
        if first == True:
            medianstr += s1[i]
            first = False
        else:
            medianstr += s2[i]
            first = True
        i += 1

    if len(s1) == len(s2):
        return medianstr
    elif len(s1) > len(s2):
        while i < len(s1):
            medianstr += s1[i]
            i += 1
    elif len(s1) < len(s2):
         while i < len(s2):
            medianstr += s2[i]
            i += 1
    return medianstr



def main():
    line = input().split()
    line.sort()
    
    if len(line) % 2 != 0:
        line = (line[(len(line)//2) ])
    else:
        line = median(line[(len(line)//2) - 1], line[(len(line)//2)])
    print(line)
    

if __name__ == "__main__":
    main()
