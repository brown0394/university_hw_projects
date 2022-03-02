def print_line():
    print("+---", end='')
def print_col():
    print("|   ", end='')
def last_col():
    print('|')
def last_line():
    print('+')
def print_box(row, col):
    j = col
    while row > 0:
        while j > 0:
            j = j - 1
            print_line()
        j = col
        last_line()
        while j > 0:
            j = j - 1
            print_col()
        last_col()
        j = col
        row = row - 1
    while j > 0:
        j -= 1
        print_line()
    last_line()
n = int(input())
m = int(input())
print_box(n, m)

###coding : utf-8
##
##def drawFloor(n):
##    if n > 0:
##        print('+', end = '')
##        for a in range(n):
##            print("---+", end = '')
##        print()
##
##def drawCol(n):
##    if n > 0:
##        print('|', end = '')
##        for a in range(n):
##            print("   |", end = '')
##        print()
##
##def main():
##    val1 = int(input())
##    val2 = int(input())
##
##    for n in range(val1):
##        drawFloor(val2)
##        drawCol(val2)
##    drawFloor(val2)
##
##if __name__ == "__main__":
##    main()
