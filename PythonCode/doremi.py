
import random

def main():
    al = ["도", "레", "미", "파", "솔", "라", "시"]
    for n in range(1,8):
        a = random.randrange(1, 8)
        print(al[a-1])


if __name__ == "__main__":
    main()
