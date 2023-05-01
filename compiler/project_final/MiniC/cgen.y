%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "data.h"
    int yyerror(const char *msg), yylex();
    int symcount = 0;
    List head = NULL;
    List cur = NULL;
    FILE* fp;
    TableHead *table[27];
    int ifcnt = 0;
    int jmpcnt = 0;
%}
%union {
    struct Node *pval;
    char  *sval;
    int    ival;
}
%token INCR DECR EQUAL LEQUAL GEQUAL WHILE
%token<ival> NUM
%token<sval> ID
%type<pval> E T F assign condition conditionend
%%
startsymb : statement
          | conditionalstate
          | startsymb conditionalstate statement
          ;
conditionalstate : flowcontrol '('conditionend')' '{'statement'}' {
      char str[15]; sprintf(str, "ujp l%d\nl%d: \0", jmpcnt, jmpcnt+1);
      jmpcnt += 2;
      cur->son = cons(mkstr(str), NULL); cur->son->kind = JMP;
      cur->son->gen = -3;
      cur->bro = cons(NULL, NULL); cur = cur->bro;
}
statement : statement expressionend
          | expressionend
          ;
expressionend : assign';' { cur->bro = cons(NULL, NULL); cur = cur->bro; }
          ;
assign    : E       { $$ = $1; if ($1->kind != IDNUM) { if ($1->kind == UNARY && $1->son->kind == IDNUM) {}
                      else {yyerror("declaration/unaryop error"); return 0;}} else { $1->gen = -2; } cur->son = $$;}
          | assign '=' E { if ($1->kind != IDNUM) {yyerror("assignment syntax error"); return 0;}
                           $$ = binary('=', $1, $3); $1->gen = -2; cur->son = $$; }
          ;
conditionend : condition { 
                  char str[4]; sprintf(str, "%d\0", ifcnt++);
                  cur->son = cons(mkstr(str), $1); cur->son->kind = JMP;
                  cur->son->gen = -2;
                  cur->bro = cons(NULL, NULL); cur = cur->bro;
              }
             ;
condition : E                    { $$ = $1; cur->son = $$; }
          | condition '<' E      { $$ = binary('<', $1, $3); cur->son = $$; }
          | condition '>' E      { $$ = binary('>', $1, $3); cur->son = $$; }
          | condition EQUAL E    { $$ = binary('=', $1, $3); $$->gen = -2; cur->son = $$; }
          | condition LEQUAL E   { $$ = binary('<', $1, $3); $$->gen = -2; cur->son = $$; }
          | condition GEQUAL E   { $$ = binary('>', $1, $3); $$->gen = -2; cur->son = $$; }
          ;
E     : E '+' T   { $$ = binary('+', $1, $3); }
      | E '-' T   { $$ = binary('-', $1, $3); }
      | T         { $$ = $1; }
      ;
T     : T '*' F   { $$ = binary('*', $1, $3); }
      | T '/' F   { $$ = binary('/', $1, $3); }
      | F         { $$ = $1; }
      ;
F     : NUM   { List newnode = cons(mkint($1), NULL); newnode->kind = INTVAL; $$ = newnode; }
      | ID    { List newnode = cons(mkstr($1), NULL); newnode->kind = IDNUM; putInTable(table, newnode->val, &symcount); $$ = newnode; }
      | '-' F     { $$ = unary('-', $2); }
      | '+' F     { $$ = unary('+', $2); }
      | INCR F    { if ($2->kind != IDNUM) {yyerror("unarry error"); return 0;} $$ = unary('+', $2); $$->gen = -2; }
      | DECR F    { if ($2->kind != IDNUM) {yyerror("unarry error"); return 0;} $$ = unary('-', $2); $$->gen = -2; }
      | '('E')'   { $$ = $2; }
      ;
flowcontrol : WHILE { char str[4]; sprintf(str, "%d\0", ifcnt++);
              cur->son = cons(mkstr(str), NULL); cur->son->kind = JMP;
              cur->bro = cons(NULL, NULL); cur = cur->bro; }
            ;
%%
int main() {
   head = cons(NULL, NULL);
   cur = head;
   fp = fopen("cgen.t", "w");
   if(!fp) return 0;
   yyparse();
   fprintf(fp, "ssp %d\n", symcount);
   generateTf(fp, head, table);
   fprintf(fp, "out\n");
   fclose(fp);
   return 0;
}
int yyerror(const char *msg) { fputs(msg, stderr); }

