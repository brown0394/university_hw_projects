SHELL = /bin/sh

sources = lex.yy.c y.tab.c data.c
headers = y.tab.h data.h

cgen: $(sources)
	gcc -o $@ $(sources)
lex.yy.c: cgen.l $(headers)
	flex $<
y.tab.c: cgen.y
	bison -dy $<
y.tab.h: cgen.y
	bison -dy $<
