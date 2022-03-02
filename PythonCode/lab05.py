lang = "Python"

##print(lang)
##
##print(lang[0].isupper())
##print(lang[-1].islower())
##
##print(lang.upper())
##print(lang)
##
##lang = lang.upper()
##print(lang)
##print(lang.isupper())
##print(lang.islower())
##
##
##lang = lang.lower()
##print(lang)
##print(lang.isupper())
##print(lang.islower())

name = ""
for i in range(len(lang)):
    if i % 2 == 0:
        name += lang[i].lower()
    else:
        name += lang[i].upper()
print(name)
