%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "data.h"
    int yyerror(const char *msg), yylex();

    List head = NULL;

%}
%union {
    struct Node *pval;
    char   cval;
    int    ival;
}
%token<ival> NUM
%token<cval> ADD SUB MUL DIV
%type<pval> E T F
%%
E     : E ADD T   { $$ = binary($2, $1, $3); head = $$; }
      | E SUB T   { $$ = binary($2, $1, $3); head = $$; }
      | T         { $$ = $1; head = $$; }
      ;
T     : T MUL F   { $$ = binary($2, $1, $3); }
      | T DIV F   { $$ = binary($2, $1, $3); }
      | F         { $$ = $1; }
      ;
F     : NUM       { List newnode = cons(mkint($1), NULL); newnode->kind = INTVAL; $$ = newnode; }
      | SUB F     { $$ = unary($1, $2); }
      | ADD F     { $$ = unary($1, $2); }
      | '('E')'   { $$ = $2; }
      ;

%%
int main() { 
   yyparse();
   FILE* fp = fopen("cgen.t", "w");
   if(!fp) return 0;
   generateTf(fp, head);
   fprintf(fp, "out\nstop\n");
   fclose(fp);
   printStack(head);
   return 0;
}
int yyerror(const char *msg) { fputs(msg, stderr); }

