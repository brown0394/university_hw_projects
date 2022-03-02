#coding : utf-8


def hamming(p_line1, p_line2):
    count = 0
    distance = 0
    while count < len(p_line1):
        if p_line1[count] != p_line2[count]:
            distance += 1
        count +=1
    return distance


def main():
    line1 = input().upper()
    line2 = input().upper()
    line1 = list(line1)
    line2 = list(line2)
    distance = hamming(line1, line2)
    print(distance)




if __name__ == "__main__":
    main()
