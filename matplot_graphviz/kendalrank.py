import itertools
from scipy import stats

a = [1, 2, 5, 4, 7, 8, 6, 3]
b = [1, 2, 3, 4, 5, 6, 7, 8]

lst = list(itertools.combinations(a, 2))
print(lst)

invers = []
norm = []

for elem in lst :
    if elem[0] > elem[1]:
        invers.append(elem)
    else:
        norm.append(elem)

print(norm)
print(invers)


result = (len(norm) - len(invers)) / len(lst)
print(len(norm))
print(len(invers))
print(result)

tau, p_val = stats.kendalltau(b ,a)
print(tau)
#euc dist = 2sqrt(x-y)^2
#jaccard a n b / a U b
#tanumoto  N(a n b) / Na + Nb - N(anb)
#dice     2 * N(anb) / Na+Nb
#overlap   N(anb) / min(Na, Nb)
#tversky   |X n Y| / |X n Y| + a(X - Y) + b|Y - X|
#켄달 (올바른) - (틀린) / 전체쌍