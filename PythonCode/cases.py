#coding : utf-8


def Sum(big, small):
    prd = big
    for n in range(small, big):
        prd += n
    return prd



def main():
    val1 = list(input())
    val2 = list(input())

    Totsum = 0
    count = 0
    while count < len(val1):
        if val1[count] == 'X' and val2[count] == 'X':
            Totsum += Sum(9, 1)
        elif val1[count] == 'X' and val2[count] != 'X':
            Totsum += Sum(9, int(val2[count]))
        elif val1[count] != 'X' and val2[count] == 'X':
            Totsum += Sum(int(val1[count]), 1)
        count +=1
    print(Totsum)


if __name__ == "__main__":
    main()
