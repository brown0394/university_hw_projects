%{
   #include <stdio.h>
   #include <ctype.h>
   int yylex();
   void yyerror(const char *s);
%}
%token NUM
%%
Exp    : Term '+' Exp {puts("Exp <- Term + Exp");}
       | Term         {puts("Exp <- Term");}
       ;
Term:    NUM          {puts("Term <- NUM");}
       ;

%%
int main() {
    yyparse(); return 0;
}
void yyerror(const char *msg) {
     fputs(msg, stderr);
}
int yylex() {
    char c = getchar();
    return (c == '\n') ? 0: isdigit(c)? NUM: c;
}
