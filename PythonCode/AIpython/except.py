a = [1, 2, 3, 4]

try:
    print(a[5])
except IndexError:
    print(a[5%4])

try:
    a = b
except NameError:
    b= 50
