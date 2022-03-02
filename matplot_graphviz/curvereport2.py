import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

x = [5, 6, 7, 9, 13, 15, 21, 25, 32, 33]
y = [177, 196, 204, 230, 248, 264, 249, 238, 172, 153]

def func(x, a, b, c) :
    return a * np.power(x-b,2) + c


popt, pcov = curve_fit(func, x, y, bounds=([-1., 18., 263.], [-0.1, 20., 265.]))
print("예측한 계수값은 popt=", popt)
perr = np.sqrt(np.diag(pcov))
print("perr=", perr)

nx = np.linspace(3,33,100)
plt.plot(nx, func(nx, *popt), 'r-', \
          label='fit: a=%5.3f, b=%5.3f, c=%5.3f' % tuple(popt))


plt.plot(x, y, '.')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.show()
