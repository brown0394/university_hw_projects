from functools import reduce

def double(num):
    return num * 2

##return "yes" if charlist(w1) == charlist(w2) else "no"

def main():
##    keylist = ['one' ,'two', 'three']
##    diclist = {x:n+1 for (n,x) in enumerate(keylist)}
##    
##    elist = [[double(x) for x in range(1, xs) if x % 3 == 0] for xs in range(10, 50)]
##    print(elist)
##    print(diclist)
    x = lambda y: y + 1
    print(x(1))
    a = list(map(lambda x: x**2, range(10)))
    print(f"maplambda : {a}")
    a = list(filter(lambda x: x%2==0, range(10)))
    print(f"filter : {a}")
    a = reduce(lambda x,y: x+y, range(1, 10+1))
    print(f"reduce : {a}")

    ns = list(range(10))
    print(f"ns : {ns}")
    ms = list(map(x, ns))
    print(f"ms : {ms}")
    ps = list(map(lambda x: 2 ** x, ns))
    print(f"ps : {ps}")
    qs = list(map(lambda x: 2 **x, ms))
    print(f"qs : {qs}")
    evens = list(filter(lambda x: x%2 == 0, ns))
    print(f"evens : {evens}")
    evens2 = evens
    print(f"by sum funiction : {sum(evens)}")
    a = reduce(lambda x, y: x+y, evens2, 10)
    print(f"by reduce function : {a}")
    a = reduce(lambda x, y: x / y, ns)
    print(a)
    
if __name__ == "__main__":
    main()
    
