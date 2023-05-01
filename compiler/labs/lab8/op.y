%{
   #include <stdio.h>
   #include <ctype.h>
   int yylex();
   void yyerror(const char *s);
%}
%token NUM
%%
Exp    : Exp '+' Term {puts("E -> E + T");}
       | Exp '-' Term {puts("E -> E - T");}
       | Term         {puts("E -> T");}
       ;
Term   : Term '*' Fin {puts("T -> T * F");}
       | Term '/' Fin {puts("T -> T / F");}
       | Fin          {puts("T -> F");}
Fin    : NUM          {puts("F -> N");}
       ;
%%
int main() {
    yyparse(); return 0;
}
void yyerror(const char *msg) {
     fputs(msg, stderr);
}
