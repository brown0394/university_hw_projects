#specifiy Precision = tp / tp+fp
#sensitivity recall = tp / tp+fn
#acc = tp + tn / tp+tn+fp+fn


tp = 3
fp = 1
tn = 6
fn = 3

precision = tp / (tp+fp)
recall = tp / (tp+fn)
acc = (tp + tn) / (tp+tn+fp+fn)

print("pr = ", precision)
print("rec = ", recall)
print("acc = ", acc)
88888
print("precision =", tp, '/', tp+fp)
print("recall =", tp, '/', tp+fn)
print("acc =", tp+tn, '/', tp+fp+tn+fn)

F1 = 2 * ((precision*recall) / (precision+recall))

print("f1 = 2 *", (precision*recall), '/', (precision+recall))
print("f1 =", F1)