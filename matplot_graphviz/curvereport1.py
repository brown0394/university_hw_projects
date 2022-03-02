import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

x = [5, 11, 15, 44, 60, 70, 75, 100, 120, 200]
y = [2.492, 8.330, 11.000, 19.394, 24.466, 27.777, 29.878, 26.952, 35.607, 46.966]


def func(x, a, b, c) :
    return a * (np.sqrt(x-b)) + c
#    return a * np.log(x-b) + c


popt, pcov = curve_fit(func, x, y, bounds=(0, [np.inf, 6., 3.]))
print("예측한 계수값은 popt=", popt)
perr = np.sqrt(np.diag(pcov))
print("perr=", perr)

nx = np.linspace(3,200,100)
plt.plot(nx, func(nx, *popt), 'r-', \
          label='fit: a=%5.3f, b=%5.3f, c=%5.3f' % tuple(popt))


plt.plot(x, y, '.')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.show()
