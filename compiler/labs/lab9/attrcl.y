%{ 
	#include <stdio.h>
	#include <ctype.h>
	int yylval;
	int yyerror(const char *s);
	int yylex();
%}
%token NUM
%%
Line    : EXP		{ printf("= %d\n", $1); }
	;
EXP 	: EXP '+' NUM	{ $$ = $1 + $3; }
	| NUM		{ $$ = $1; }
	;
%%
int main() { yyparse(); return 0; }
int yyerror(const char *msg) { fputs(msg, stderr); return -1; }
int yylex() { 
    //static char numbuff[10];
    //static int buffidx = 0;
    int c = getchar();
    //(c == '\n')? c=0: isdigit(c)? numbuff[buffidx++] = c - '0';
    return (c == '\n')? 0: isdigit(c)? yylval = c - '0', NUM: c;
}

