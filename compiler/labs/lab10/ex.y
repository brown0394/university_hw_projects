%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int yyerror(const char *msg), yylex();
%}
%union {
    char *sval;
    int   ival;
}
//%left '+' '.'
%token <sval> NAME
%token <ival> NUMBER
%type  <sval> sExp sTerm
%type  <ival> iExp nTerm
%%
Start    : iExp           { printf("= %d\n", $1); }
	 | sExp           { printf("= '%s'\n", $1); }
         ;
iExp     : iExp '+' nTerm { $$ = $1 + $3; }
	 | nTerm          { $$ = $1; }
	 ;
nTerm    : NUMBER         { $$ = $1; }
	 ;
sExp     : sExp '.' sTerm { int l1 = strlen($1), l2 = strlen($3);
			    $$ = calloc(l1+l2+1, 1); strcpy($$, $1);
			    strcpy($$+l1, $3); }

	 | sTerm          { $$ = calloc(strlen($1) + 1, 1);
			    strcpy($$, $1); }
	 ;
sTerm    : NAME           { $$ = calloc(strlen($1) + 1, 1);
			    strcpy($$, $1); }
	 ;
%%
int main() { yyparse(); return 0; }
int yyerror(const char *msg) { fputs(msg, stderr); }
