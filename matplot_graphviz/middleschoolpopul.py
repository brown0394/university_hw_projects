import matplotlib.pyplot as plt
import numpy as np

from matplotlib import font_manager, rc
font_name = font_manager.FontProperties(fname="c:/Windows/Fonts/H2GTRE.TTF").get_name()
rc('font', family=font_name)

x = list(range(1996, 2020))
y = [2343, 2179, 2033, 1926, 1869, 1847, 1863, 1913, 1993, 2064, 2104,\
	 2095, 2070, 2034, 1985, 1914, 1867, 1818, 1719, 1578, 1458, 1385,\
     1340, 1318]


def func(x, a, b, c, d, e ,f) :
    return (a * np.power(x-b, 4)) + (d * np.power(x-b, 3))+ (e * np.power(x-b, 2)) + (f*(x-b)) + c


nx = np.linspace(1995,2020,100)



fit_1 = np.polyfit(x,y,4)  # 1차로 mapping 함. 결과는 2개의 실수(기울기와 절편)
print("Linear Fitted data = ", fit_1)
fit_fn1 = np.poly1d(fit_1)
plt.plot(nx, fit_fn1(nx), '-r')

plt.title('1000단위 중등 학령인구 증감')
plt.plot(x, y, '.')
plt.xlabel('년도')
plt.ylabel('인구수')
plt.show()
