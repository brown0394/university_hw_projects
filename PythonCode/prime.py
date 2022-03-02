#coding : utf-8


def prime(num):
    primelist = []
    count = 1
    for n in range(2, num+1):
        while(num % n == 0):
            num = num / n
            primelist.append(n)
    if len(primelist) > 1:
        for n in primelist:
            if count != len(primelist):
                print(n, end=" * ")
            else:
                print(n)
            count += 1
    else:
        print("this is a prime number")

def main():
    num = int(input())
    prime(num)


if __name__ == "__main__":
    main()
