#coding : utf-8

def masking(filt, line, shape):
    count = 0
    for n in line:
        if n in filt:
            line[count] = shape
            count +=1
        else:
            count +=1

def main():
    vowels = "aeiou"
    newline = list(input())
    shape = input()
    masking(vowels, newline, shape)
    newline = ''.join(newline)
    print(newline)
    


if __name__ == "__main__":
    main()
