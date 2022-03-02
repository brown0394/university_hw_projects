import matplotlib.pyplot as plot
import seaborn as sns

from matplotlib import font_manager, rc
font_name = font_manager.FontProperties(fname="c:/Windows/Fonts/H2GTRE.TTF").get_name()
rc('font', family=font_name)



plot.title('10만명당 자살율 년도별 추이')
plot.xlabel('년도')
plot.ylabel('자살율')


plot.xlim(7.8, 19.2)
Fin = [20.6, 20.4, 18.6, 17.9, 17, 17.2, 15.4, 14, 15.2, 15.9, 16.2, 15.3]
Kor = [28.6, 34.2, 34, 34.5, 30.2, 30.6, 29, 28, 27.2, 25.8, 28.6, 28.6]
Peru =[2.7, 3.3, 3.5, 3.3, 3.2, 3.1, 2.9, 2.7, 2.6, 2.7, 2.8, 2.8]
years = list(range(8, 20))
sns.regplot(x = years, y = Fin, ci=None, 
line_kws={'color': 'deepskyblue'}, scatter_kws={'color': 'turquoise'}, label='핀란드')
sns.regplot(x = years, y = Kor, ci=None, 
line_kws={'color': 'tomato'}, scatter_kws={'color': 'sandybrown'}, label='대한민국')
sns.regplot(x = years, y = Peru, ci=None, 
line_kws={'color': 'yellowgreen'}, scatter_kws={'color': 'chartreuse'}, label='페루')

plot.legend()
plot.show()