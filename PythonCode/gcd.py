def gcd(val1, val2):
    if val1 > val2:
        big = val1
        small = val2
    elif val1 == val2:
        return val1
    else:
        big = val2
        small = val1
    rem = big % small
    if rem == 0:
        return small
    else:
        return gcd(small, rem)

def main():
    for n in range(1, 1000):
        a = (5*n) + 3
        b = (7*n) + 4
        c = gcd(b, a)
        print(c)
##    a = input().split()
##    c=[]
##    for n in a:
##        c.append(int(n))
##    b = gcd(c[0], c[1])


if __name__ == "__main__":
    main()
