SHELL = /bin/sh

sources = lex.yy.c y.tab.c
headers = y.tab.h

sexpr: $(sources)
	gcc -o $@ $(sources)
lex.yy.c: sexpr.l $(headers)
	flex $<
y.tab.c: sexpr.y
	bison -dy $<
y.tab.h: sexpr.y
	bison -dy $<
