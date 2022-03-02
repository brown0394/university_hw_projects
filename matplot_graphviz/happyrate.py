import matplotlib.pyplot as plot
import seaborn as sns

from matplotlib import font_manager, rc
font_name = font_manager.FontProperties(fname="c:/Windows/Fonts/H2GTRE.TTF").get_name()
rc('font', family=font_name)



plot.title('행복도 년도별 추이')
plot.xlabel('년도')
plot.ylabel('행복도')


plot.xlim(11.9, 20.1)
Fin = [7.389, 7.406, 7.413, 7.469, 7.632, 7.769, 7.809, 7.842]
Kor = [6.267, 5.984, 5.835, 5.838, 5.875, 5.895, 5.872, 5.845]
Peru =[5.776, 5.824, 5.743, 5.715, 5.663, 5.697, 5.797, 5.84]
years = [12, 14, 15, 16, 17, 18, 19, 20]
sns.regplot(x = years, y = Fin, ci=None, 
line_kws={'color': 'deepskyblue'}, scatter_kws={'color': 'turquoise'}, label='핀란드')
sns.regplot(x = years, y = Kor, ci=None, 
line_kws={'color': 'tomato'}, scatter_kws={'color': 'sandybrown'}, label='대한민국')
sns.regplot(x = years, y = Peru, ci=None, 
line_kws={'color': 'yellowgreen'}, scatter_kws={'color': 'chartreuse'}, label='페루')

plot.legend()
plot.show()