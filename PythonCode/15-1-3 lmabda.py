import functools

def mysum(*ls):#*은 리스트로 받게 해줌
    s = 0
    for n in ls:
        s += n
    return s

if __name__ == "__main__":
    print(sum([1, 2]))
    print(sum([1, 2, 3]))
    print(mysum(1, 2, 3, 4))
    mysum2 = lambda *ls: functools.reduce(lambda x, y: x + y, ls, 0)
    print(mysum2(1, 2, 3, 4, 5))
    prod = lambda *ls: functools.reduce(lambda x, y: x * y, ls, 1)
    print(prod(1, 2, 3))
    ns = list(range(1, 11))
    print(sum(ns))
    print(prod(ns))
    print(prod(*ns))
    

