#coding : utf-8

def binary(num, binarylist):
    if num < 2:
        binarylist.append(num)
        return binarylist
    binarylist.append(num%2)
    num = num //2
    return binary(num, binarylist)



def main():
    val = input().split()
    val = list(map(int, val))
    divisior = int(input())
    numlist = [n for n in range(val[0], val[1]+1) if n % divisior == 0]

    onesum = 0
    for n in numlist:
        blist = []
        binary(n, blist)
        onesum += blist.count(1)
    print(onesum)


if __name__ == "__main__":
    main()
