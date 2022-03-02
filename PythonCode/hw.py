#coding: utf-8

def change_member(p_line, p_masking):
    current = 0
    for n in p_line:
        if n in p_masking:
            p_line[current] = p_line[current].upper()
            return p_line
        current += 1

def divide(p_line, p_masking):
    first = 0
    newline = list()
    sentence = list()
    for n in p_line:
        if n != " ":
            newline += n
        elif n == " ":
            if first == 0:
                first = 1
            else :
                sentence += ' '
            sentence += change_member(newline, p_masking)
            newline = list()
    if 1 == first:
        sentence += ' '
    sentence += change_member(newline, p_masking)
    return sentence


def main():
    vowels = list("aeiou")
    line = (input())
    line = line.lower()
    line = list(line)
    line = divide(line, vowels)
    print("".join(line))


if __name__ == "__main__":
    main()
