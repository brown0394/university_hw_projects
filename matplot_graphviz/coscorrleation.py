# cos theta = x . y / |x||y|
import numpy


a = [1, 2, 0, 1]
b = [2, 4, 0, 2]

sq1 = 0
sq2 = 0

res = 0
for i in range(0, len(a)):
    res += (a[i] * b[i])
    sq1 += pow(a[i], a[i])
    sq2 += pow(b[i], b[i])

sq1 = numpy.sqrt(sq1)
sq2 = numpy.sqrt(sq2)

costheta = res / (sq1 * sq2)

print(costheta)

