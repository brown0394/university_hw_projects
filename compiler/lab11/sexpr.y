%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"

int yylex();
void yyerror(const char* s);
struct Data* root;
%}

%union {
 char* sval;
 int ival;
 char cval;
 struct Data* dval;
 struct Node* lval;
}
%token <ival> NUM
%token <sval> NAME
%token <cval> '+' '-' '*' '/' '%'
%type  <dval> start sexpr atom list
%type  <lval> members
%%
start    : sexpr           { root = $$; }
         ;
sexpr    : list            { $$ = $1; }
         | atom            { $$ = $1; }
         ;
list     : '('members')'   { $$ = mklst($2); }
         ;
members  :                 { $$ = NULL; }
         | sexpr members   { $$ = cons($1, $2); }
	 ;
atom	 : NUM		   { $$ = mkint($1); }
 	 | NAME		   { $$ = mkstr($1); }
 	 | '+'		   { $$ = mkchr($1); }
 	 | '-'		   { $$ = mkchr($1); }
 	 | '*'		   { $$ = mkchr($1); }
 	 | '/'		   { $$ = mkchr($1); }
 	 | '%'		   { $$ = mkchr($1); }
	 ;
%%
int main() {
    yyparse();
    printf("%s\n", prdata(root));
    printf("%d\n", getArea(root));

    return 0;	
}
void yyerror(const char* msg) {
     fputs(msg, stderr);
     exit(-1);
}
