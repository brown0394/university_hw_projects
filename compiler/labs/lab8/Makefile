SHELL = /bin/sh

sources = lex.yy.c y.tab.c
headers = y.tab.h

assign5: $(sources)
	gcc -o $@ $(sources)
lex.yy.c: assign5.l $(headers)
	flex $<
y.tab.c: assign5.y
	bison -dy $<
y.tab.h: assign5.y
	bison -dy $<
