import matplotlib.pyplot as plot
import seaborn as sns

from matplotlib import font_manager, rc
font_name = font_manager.FontProperties(fname="c:/Windows/Fonts/H2GTRE.TTF").get_name()
rc('font', family=font_name)



plot.title('1000명당 출산율 년도별 추이')
plot.xlabel('년도')
plot.ylabel('출산율')



Fin = [11.22, 11.136, 11.051, 10.967, 10.882, 10.798, 10.509, 10.219, 9.93, 9.64, 9.351, 9.197]
Kor = [9.318, 9.244, 9.169, 9.095, 9.02, 8.946, 8.644, 8.342, 8.04, 7.738, 7.436, 7.303]
Peru =[21.943, 21.397, 20.851, 20.306, 19.76, 19.214, 18.991, 18.768, 18.544, 18.321, 18.098, 17.867]
years = list(range(8, 20))
plot.xlim(min(years)-0.2, max(years)+0.2)
sns.regplot(x = years, y = Fin, ci=None, 
line_kws={'color': 'deepskyblue'}, scatter_kws={'color': 'turquoise'}, label='핀란드')
sns.regplot(x = years, y = Kor, ci=None, 
line_kws={'color': 'tomato'}, scatter_kws={'color': 'sandybrown'}, label='대한민국')
sns.regplot(x = years, y = Peru, ci=None, 
line_kws={'color': 'yellowgreen'}, scatter_kws={'color': 'chartreuse'}, label='페루')

plot.legend()
plot.show()