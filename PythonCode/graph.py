def print_line(list_c, shape):
    a = 0
    for i in list_c:
        a += int(i)
        print(shape * a)

def main():
    c = input()
    a_list = c.split()
    c = a_list[0]
    a_list.pop(0)
    print_line(a_list, c)

main()
