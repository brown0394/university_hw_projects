#------------------공학작문 기말고사 7번 문제-----------------------------

import matplotlib.pyplot as plot
plot.figure(figsize=(8,5)) # 인치

Weight = [ (1, 67.3),  (2,67.1),  (4,66.4),  (8,65.7), (10, 64.9),
           (11, 65.3), (13,63.9), (14,64.1), (18,64.7), (20, 64.1),
           (25, 64.5), (26,63.4), (27,63.6), (31,62.7), (32, 62.5)
         ]

day = []
weighty = []
for w in Weight :
    day.append(w[0])
    weighty.append(w[1])

plot.title("Problem 06, Weight Regression:")

def func(x, a, b, c) :
    return 


plot.xlabel('days')
plot.ylabel('weight')
plot.plot(day, weighty, '.')
plot.show( )


