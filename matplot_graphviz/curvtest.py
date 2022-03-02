from math import sin
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

y = [6.2, 6.8, 9.2, 9.6, 7.6, 5.9, -5.5, 11.5, 9.1, 4.9, 7.7,
3.1, 5.2, 4.3, 5.3, 5.8, 3.0, 0.8, 6.8, 3.7, 2.4, 3.2, 3.2, 2.8, 2.9, 3.2, 2.7, 2.0]
x = list(range(1992, 2020))

print(y)
def func(x, a, b) :
    return 


popt, pcov = curve_fit(func, x, y)#, bounds=(0, [np.inf, 6., 3.]))
print("예측한 계수값은 popt=", popt)
perr = np.sqrt(np.diag(pcov))
print("perr=", perr)

nx = np.linspace(1991,2020,100)
plt.plot(nx, func(nx, *popt), 'r-')#, \
         # label='fit: a=%5.3f, b=%5.3f, c=%5.3f' % tuple(popt))
plt.plot(x, y, '.')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.show()
