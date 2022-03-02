##class Point:
##    def __init__(self, x, y):
##        assert x > 0 and y > 0, "positive coorditantes only"
##        self.x, self.y = x, y
##    def __str__(self):
##        return f"({self.x}, {self.y})"
##
##
##class NamedPoint(Point):
##    def __init__(self, name, x, y):
##        Point.__init__(self, x, y)
##        self.name = name
##    def __str__(self,):
##        wv = Point.__str__(self)
##        return self.name + wv


def main():
##    a = Point(2, 3)
##    b = NamedPoint('A', -2, 3)
##    pnts = [a, b]
##
##    for p in pnts:
##        print(p)
        
##    for y in range(2):
##        for x in range(3):
##            p = Point(x, y)
##            print(p)
    try:
        line = input()
##        amount = sum(map(ord, line))
        amount = int(line)
        number = len(line)
        share = amount / number
        print(share)
    except ZeroDivisionError:
        print("Error: cant divide-by-zero")
    except ValueError:
        print("Error: Incorrect Type is typed")
    except ZeroDivisionError:
        print("Error: Undefined Error.. Good luck")
##    else #정상 작동시
##  finally# 문제가 있던 없던. 이거 작동하고 끝.
##  raise NameError('what?')  with   as     <-이거 확인   

if __name__ == "__main__":
    main()
 
