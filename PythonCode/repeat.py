def repeat(c, n):
    print(c * n)

def box():
    print('+---+')
    print('|   |')
    print('+---+')

n = int(input())
m = n
while n > 0:
    box()
    n = n - 1
