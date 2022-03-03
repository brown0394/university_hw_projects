SHELL = /bin/sh

sources = lex.yy.c y.tab.c
headers = y.tab.h

expr: $(sources)
	gcc -o $@ $(sources)
lex.yy.c: expr.l $(headers)
	flex $<
y.tab.c: expr.y
	bison -dy $<
y.tab.h: expr.y
	bison -dy $<
