SHELL = /bin/sh

sources = lex.yy.c y.tab.c
headers = y.tab.h

ast: $(sources)
	gcc -o $@ $(sources)
lex.yy.c: ast.l $(headers)
	flex $<
y.tab.c: ast.y
	bison -dy $<
y.tab.h: ast.y
	bison -dy $<
