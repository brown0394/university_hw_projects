#coding : utf-8



##def main():
##    val = input().split()
##    xval = int(input())
##    val = list(map(int, val))
##    val.reverse()
##
##    valist = [(x, y) for (x, y) in zip(range(len(val)), val)]
##    sumcal = lambda x, y: y*(xval**x)
##
##    sumval = 0
##    for x, y in valist:
##        sumval += sumcal(x, y)
##
##    print(sumval)

from functools import reduce

    
def main():
    val = input().split()
    xval = int(input())
    val = list(map(int, val))
    val.reverse()

    valist = [(x, y) for (x,y) in zip(range(len(val)), val)]
    sumcal = lambda x, y : y * (xval**x)

    sumval = [sumcal(x,y) for x,y in valist]
    result = reduce(lambda x, y: x+y, sumval)
    print(result)


if __name__ == "__main__":
    main()
