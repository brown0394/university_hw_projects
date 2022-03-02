#coding: utf-8

def change_member(p_symbol, p_line, p_masking):
    current = 0
    for n in p_line:
        if n in p_masking:
            p_line[current] = p_symbol
        current += 1
    return p_line

def main():
    vowels = list("aeiou")
    line = list(input())
    symbol = input()
    line = change_member(symbol, line, vowels)
    print("".join(line))

if __name__ == "__main__":
    main()
