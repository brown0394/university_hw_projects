class Polynom:
    def __init__(self, plist):
        self.plist = plist
    def __str__(self):
        newstr = ""
        first = True
        for (i,n) in self.plist:
            if(first == True and i > 1):
                newstr += f"x^{i}"
            if(i > 1):
                newstr += f"+ x^{i}"
        return newstr
    def __add__(self, q):
        vals1 = []
        vals2 = []
        for (i, n) in self.plist:
            vals1.append(n)
        for (i, n) in q.plist:
            vals2.append(n)
        count = 0
        length = 0
        if(len(vals1) > len(vals2)):
            length = len(vals1)
            diffrence = len(vals1) - len(vals2)
            while(diffrence > 0):
                vals2.append(0)
                diffrence -= 1
        elif(len(vals1) < len(vals2)):
            length = len(vals2)
            diffrence = len(vals2) - len(vals1)
            while(diffrence > 0):
                vals1.append(0)
                diffrence -= 1
        else:
            length = len(vals2)
        while(count < length):
            vals1[count] += vals2[count]
            count += 1
        return list(enumerate(vals1))

def poly(p_list):
    newvalist = []
    newvalist = [(x, y) for (x,y) in zip(range(len(p_list)), p_list)]
    return newvalist


def main():
    val1 = input().split()
    val1 = list(map(int, val1))
    val1.reverse()
    val1 = poly(val1)

    val2 = input().split()
    val2 = list(map(int, val2))
    val2.reverse()
    val2 = poly(val2)

    poly1 = Polynom(val1)
    poly2 = Polynom(val2)
    poly1 = poly1 + poly2
    print(poly1)




if __name__ == "__main__":
    main()
