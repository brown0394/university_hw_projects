%{
   #include <stdio.h>
   #include <ctype.h>
   int yylex();
   void yyerror(const char *s);
%}
%token NUM
%%
EXP    : EXP '+' NUM {puts("EXP <- EXP + NUM");}
       | NUM         {puts("EXP <- NUM");}
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
