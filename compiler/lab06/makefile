tokcnt: tokcnt.c
	gcc tokcnt.c -o main
tokcnt.c: lex.yy.c
	mv lex.yy.c tokcnt.c
lex.yy.c: tokcnt.l
	flex tokcnt.l
