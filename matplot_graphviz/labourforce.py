import matplotlib.pyplot as plot
import seaborn as sns

from matplotlib import font_manager, rc
font_name = font_manager.FontProperties(fname="c:/Windows/Fonts/H2GTRE.TTF").get_name()
rc('font', family=font_name)



plot.title('실업율 년도별 추이')
plot.xlabel('년도')
plot.ylabel('실업율')



Fin = [6.37, 8.25, 8.39, 7.78, 7.69, 8.19, 8.66, 9.38, 8.82, 8.64, 7.36, 6.7]
Kor = [3.2, 3.6, 3.7, 3.4, 3.2, 3.1, 3.5, 3.55, 3.65, 3.65, 3.82, 3.75]
Peru =[3.82, 3.73, 3.3, 3.27, 2.94, 3.21, 2.85, 2.92, 3.38, 3.35, 3.18, 3.03]
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