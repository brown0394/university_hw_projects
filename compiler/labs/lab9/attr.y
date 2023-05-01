%{ 
	#include <stdio.h>
	#include <ctype.h>
	int yylval;
	int yyerror(const char *msg);
	int yylex();
	#define max(x,y) (x>y)?x:y
%}
%token NUMBER
%%
Line    : S { printf("max depth = %d \n", $1); }
	;
S 	: '(' S ')' S { $$ = max($2 + 1, $4); }
	| { $$ = 0; }
	;
%%
int main() { yyparse(); return 0; }
int yyerror(const char *msg) { fputs(msg, stderr); return -1; }
int yylex() { int c = getchar();
return (c == '\n')? 0: (c == '(' || c == ')')? c: yyerror("Error");
}

