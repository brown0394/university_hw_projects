
import random

def main():
    mo = ["a", "e", "i", "o", "u", "y", "w", "io", "ee", "ae", "ea", "io", "ou"]
    ja = ["q", "r", "t", "p", "s", "d", "f", "g", "j", "k", "l", "z", "x", "c", "v", "b", "n", "m", "ng", "y", "w"]
    for n in range(0,random.randrange(2, 5)+1):
        if n % 2 != 0:
            print(mo[random.randrange(0, len(mo))], end="")
        else:
            print(ja[random.randrange(0, len(ja))], end="")



if __name__ == "__main__":
    main()
