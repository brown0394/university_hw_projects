import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit


x = [5, 11, 12, 17, 26, 37, 45, 60, 70, 72]
y = [2.800, 1.500, 2.450, 3.200, 27.450, 48.800, 64.200, 141.450,
     201.450, 226.050]


def func(x, a, b, c) :
    return a * np.power(x-b,2) + c


popt, pcov = curve_fit(func, x, y, bounds=(0, [np.inf, 10., 10.]))
print("예측한 계수값은 popt=", popt)
perr = np.sqrt(np.diag(pcov))
print("perr=", perr)

nx = np.linspace(5,72,100)
plt.plot(nx, func(nx, *popt), 'r-', \
          label='fit: a=%5.3f, b=%5.3f, c=%5.3f' % tuple(popt))


plt.plot(x, y, '.')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.show()

